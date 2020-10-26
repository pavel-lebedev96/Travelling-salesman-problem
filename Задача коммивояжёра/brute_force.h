#pragma once
#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H
#include "route_methods.h"

class brute_force : public route_methods
{
	coordinates *best_route;
	double best_length;
	void thread_brute_force(int & cur_pos, coordinates *cur_route, double & cur_length, coordinates *available, int & available_size);
	void thread_manage(int start_point);
public:
	brute_force(coordinates depart, const std::string& file_name);
	brute_force(coordinates depart, const std::vector<coordinates> &points);
	~brute_force();
	void make_route();
};
#endif //BRUTE_FORCE_H