#pragma once
#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H
#include "route_methods.h"
class greedy_algorithm :public route_methods
{
private:
	size_t nearest_point(const coordinates & from, const std::vector <coordinates> & available);
public:
	greedy_algorithm(coordinates depart, const std::string& file_name);
	greedy_algorithm(coordinates depart, const std::vector<coordinates>& points);
	greedy_algorithm(const std::vector<coordinates>& route, const std::vector<coordinates>& points);
	void make_route(bool loop);
};
#endif // GREEDY_ALGORITHM_H