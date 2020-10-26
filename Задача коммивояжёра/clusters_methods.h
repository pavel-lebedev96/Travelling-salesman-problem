#pragma once
#ifndef CLUSTERS_METHODS_H
#define CLUSTERS_METHODS_H
#include "brute_force.h"
#include "greedy_algorithm.h"
class clustersMethod : public route_methods
{
	clusterAnalysis cA;
	int clustersNum;
public:
	clustersMethod(coordinates depart, const std::string& file_name, int clustersNum);
	void make_route();
};
#endif // !CLUSTERS_METHODS_H