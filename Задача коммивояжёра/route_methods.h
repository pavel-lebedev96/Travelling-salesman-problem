#pragma once
#ifndef ROUTE_METHODS_H
#define ROUTE_METHODS_H
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#define empty_coordinates coordinates(-1,-1)
struct coordinates
{
	double x, y;
	int num;
	coordinates();
	coordinates(double x, double y, int num = -1);
	coordinates(const coordinates &a);
	coordinates & operator=(const coordinates & a);
	bool operator==(const coordinates & a) const;
};
/*длина от from до to*/
double length(const coordinates& from, const coordinates& to);
class Сluster
{
	std::vector<coordinates> points;
	void calcCenter();
public:
	coordinates center;
	void addPoints(const std::vector<coordinates>& _points);
	std::vector<coordinates>& getPoints();
	operator coordinates();
};
class clusterAnalysis
{
	std::vector<Сluster> clusters;
	std::vector<std::vector<double>> distanceMtrx;
	std::pair<int, int> minDistance();
	void makeDistanceMtrx();
	void combineClusters(const std::pair<int, int>& cl);
	void file_input(const std::string& file_name);
public:
	clusterAnalysis(const std::string& file_name);
	std::vector<Сluster> getClusters();
	void file_output();
	void clustering( int clustersNum);
	friend class clustersMethod;
};
std::vector<coordinates> clustersToPoints(const std::vector<Сluster>& clusters);
std::vector<int> routeToClustersPos(const std::vector<coordinates>& route);
class route_methods
{
protected:
	/*входные данные*/
	std::vector<coordinates> points;
	/*маршрут*/
	std::vector<coordinates> route;
	/*длина маршрута*/
	double route_length;
	/*пункт отправление*/
	coordinates depart;
	/*разделение x и y по разным файлам*/
	void divide_xy();
	void file_input(const std::string& file_name);
public:
	void file_output();
	std::vector<coordinates> getRoute();
	double getRouteLength();
	route_methods() {};
	route_methods(coordinates depart, const std::string& file_name);
	route_methods(coordinates depart, const std::vector<coordinates>& points);
	route_methods(const std::vector<coordinates>& route, const std::vector<coordinates>& points);
};
#endif// ROUTE_METHODS_H