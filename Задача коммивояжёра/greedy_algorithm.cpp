#include "greedy_algorithm.h"
greedy_algorithm::greedy_algorithm(const std::vector<coordinates>& route, const std::vector<coordinates>& points) :route_methods(route, points){}
greedy_algorithm::greedy_algorithm(coordinates depart, const std::string& file_name) : route_methods(depart, file_name){}
greedy_algorithm::greedy_algorithm(coordinates depart, const std::vector<coordinates>& points) : route_methods(depart, points) {}

void greedy_algorithm::make_route(bool loop)
{
	size_t pos;
	std::vector<coordinates> available = points;
	if (route.empty())
		route.push_back(depart);
	while (!available.empty())
	{
		pos = nearest_point(route.back(), available);
		route_length += length(route.back(), available[pos]);
		route.push_back(available[pos]);
		available.erase(available.begin() + pos);
	}
	if (loop)
	{
		route_length += length(route.back(), depart);
		route.push_back(depart);
	}
}
size_t greedy_algorithm::nearest_point(const coordinates & from, const std::vector <coordinates> & available)
{
	double min_length = DBL_MAX, temp;
	size_t min_pos;
	for (size_t i = 0; i < available.size(); ++i)
	{
		temp = length(from, available[i]);
		if (temp < min_length)
		{
			min_length = temp;
			min_pos = i;
		}
	}
	return min_pos;
}