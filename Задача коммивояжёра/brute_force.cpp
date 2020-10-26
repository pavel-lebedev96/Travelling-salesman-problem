#include "brute_force.h"
brute_force::brute_force(coordinates depart, const std::string& file_name) :route_methods(depart, file_name)
{
	best_length = DBL_MAX;
	best_route = new coordinates[points.size() + 2];
}
brute_force::brute_force(coordinates depart, const std::vector<coordinates>& points) : route_methods(depart, points)
{
	best_length = DBL_MAX;
	best_route = new coordinates[points.size() + 2];
}
brute_force::~brute_force()
{
	delete[] best_route;
}
void brute_force::thread_brute_force(int & cur_pos, coordinates * cur_route, double & cur_length, coordinates * available, int & available_size)
{
	bool is_empty = true;
	double temp_length;
	coordinates temp_coordinates;
	for (int i = 0; i < available_size; ++i)
	{
		if (available[i] == empty_coordinates) continue;
		is_empty = false;
		temp_coordinates = available[i];
		temp_length = length(cur_route[cur_pos], temp_coordinates);
		++cur_pos;
		cur_route[cur_pos] = temp_coordinates;
		cur_length += temp_length;
		available[i] = empty_coordinates;
		if ((cur_length < best_length))
			thread_brute_force(cur_pos, cur_route, cur_length, available, available_size);
		available[i] = temp_coordinates;
		cur_length -= temp_length;
		--cur_pos;
	}
	if (is_empty)
	{
		temp_length = length(cur_route[cur_pos], depart);
		++cur_pos;
		cur_route[cur_pos] = depart;
		cur_length += temp_length;
#pragma omp critical
		{
			if (cur_length < best_length)
			{
				for (int i = 0; i <= cur_pos; ++i)
					best_route[i] = cur_route[i];
				best_length = cur_length;
			}
		}
		cur_length -= temp_length;
		--cur_pos;
	}
}

void brute_force::thread_manage(int start_point)
{
	double cur_length = 0;
	int cur_pos = 0;
	int points_num = points.size();
	coordinates *available = new coordinates[points_num];
	coordinates *cur_route = new coordinates[points_num + 2];
	for (int i = 0; i < points_num; ++i)
		available[i] = points[i];

	cur_route[cur_pos] = depart;
	cur_length += length(cur_route[cur_pos], available[start_point]);
	++cur_pos;
	cur_route[cur_pos] = available[start_point];
	available[start_point] = empty_coordinates;
	thread_brute_force(cur_pos, cur_route, cur_length, available, points_num);
	delete[]cur_route;
	delete[]available;
}

void brute_force::make_route()
{
	int points_num = points.size();
#pragma omp parallel for
	for (int i = 0; i < points_num; ++i)
		thread_manage(i);
	for (int i = 0; i < points_num + 2; ++i)
		route.push_back(best_route[i]);
	route_length = best_length;
}