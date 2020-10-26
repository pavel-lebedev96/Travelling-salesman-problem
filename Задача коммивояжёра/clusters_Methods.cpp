#include "clusters_methods.h"

clustersMethod::clustersMethod(coordinates depart, const std::string& file_name, int clustersNum):cA(file_name)
{
	this->depart = depart;
	this->route = { depart };
	this->clustersNum = clustersNum;
	this->route_length = 0;
}

void clustersMethod::make_route()
{
	cA.clustering(clustersNum);
	brute_force bf(depart, clustersToPoints(cA.clusters));
	bf.make_route();
	std::vector<coordinates> temp_route;
	std::vector<int> clusterPos = routeToClustersPos(bf.getRoute());
	for (int i = 0; i < cA.clusters.size(); i++)
	{
		points = cA.clusters[clusterPos[i]].getPoints();
		greedy_algorithm ga(route, points);
		ga.make_route(false);
		route = ga.getRoute();
		route_length += ga.getRouteLength();
	}
	route_length += length(route.back(), depart);
	route.push_back(depart);
}
