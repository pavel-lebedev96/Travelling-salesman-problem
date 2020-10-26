#include "route_methods.h"
coordinates::coordinates()
{
	x = -1;
	y = -1;
	num = -1;
}
coordinates::coordinates(double x, double y, int num)
{
	this->x = x;
	this->y = y;
	this->num = num;
}
coordinates::coordinates(const coordinates & a)
{
	*this = a;
}
coordinates & coordinates::operator=(const coordinates & a)
{
	this->x = a.x;
	this->y = a.y;
	this->num = a.num;
	return *this;
}
bool coordinates::operator==(const coordinates & a) const
{
	return this->x == a.x && this->y == a.y;
}
double length(const coordinates& from, const coordinates& to)
{
	return hypot(to.x - from.x, to.y - from.y);
}

std::vector<coordinates> clustersToPoints(const std::vector<Ñluster>& clusters)
{
	std::vector<coordinates> result;
	for (int i = 0; i < clusters.size(); i++)
		result.push_back(coordinates(clusters[i].center.x, clusters[i].center.y, i));
	return result;
}

std::vector<int> routeToClustersPos(const std::vector<coordinates>& route)
{
	std::vector<int> result;
	for (auto i : route)
		if (i.num != -1)
			result.push_back(i.num);
	return result;
}

void Ñluster::calcCenter()
{
	center = coordinates(0, 0);
	for (auto i : points)
	{
		center.x += i.x;
		center.y += i.y;
	}
	center.x /= points.size();
	center.y /= points.size();
}
void Ñluster::addPoints(const std::vector<coordinates>& _points)
{
	points.insert(points.end(), _points.begin(), _points.end());
	calcCenter();
}
std::vector<coordinates>& Ñluster::getPoints()
{
	return points;
}
Ñluster::operator coordinates()
{
	return this->center;
}
std::pair<int, int> clusterAnalysis::minDistance()
{
	int n = distanceMtrx.size();
	std::pair<int, int> minPos;
	double minValue = DBL_MAX;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1 - i; j++)
			if (distanceMtrx[i][j] < minValue)
			{
				minValue = distanceMtrx[i][j];
				minPos = { i,i + j + 1 };
			}
	return minPos;
}

void clusterAnalysis::makeDistanceMtrx()
{
	int n = clusters.size();
	distanceMtrx.resize(n - 1);
	for (int i = 0; i < n - 1; i++)
	{
		distanceMtrx[i].resize(n - 1 - i);
		for (int j = 0; j < n - 1 - i; j++)
			distanceMtrx[i][j] = length(clusters[i], clusters[i + j + 1]);
	}
}

void clusterAnalysis::combineClusters(const std::pair<int, int>& clPos)
{
	std::vector<coordinates> points = clusters[clPos.second].getPoints();
	clusters[clPos.first].addPoints(points);
	clusters.erase(clusters.begin() + clPos.second);
	makeDistanceMtrx();
}
void clusterAnalysis::file_input(const std::string& file_name)
{
	std::ifstream file(file_name);
	std::vector<coordinates> points;
	coordinates point;
	while (file >> point.x >> point.y)
	{
		std::vector<coordinates> points = { point };
		Ñluster cluster;
		cluster.addPoints(points);
		clusters.push_back(cluster);
	}
	file.close();

	makeDistanceMtrx();
}
clusterAnalysis::clusterAnalysis(const std::string &file_name)
{
	file_input(file_name);
}

std::vector<Ñluster> clusterAnalysis::getClusters()
{
	return clusters;
}
void clusterAnalysis::file_output()
{
	std::ofstream fileX("clusters_X.txt");
	std::ofstream fileY("clusters_Y.txt");
	std::vector<coordinates> points;
	for (int i = 0; i < clusters.size(); i++)
	{
		fileX << i << ":" << std::endl;
		fileY << i << ":" << std::endl;
		points = clusters[i].getPoints();
		for (int j = 0; j < points.size(); j++)
		{
			fileX << points[j].x << std::endl;
			fileY << points[j].y << std::endl;
		}
	}
	fileX.close();
	fileY.close();
}
void clusterAnalysis::clustering(int k)
{
	while (clusters.size() > 1 && clusters.size() > k)
	{
		std::pair<int, int> minPos = minDistance();
		combineClusters(minPos);
	}
}
void route_methods::file_input(const std::string& file_name)
{
	std::ifstream file(file_name);
	coordinates temp;
	while (file >> temp.x >> temp.y)
		points.push_back(temp);
	file.close();
}
void route_methods::file_output()
{
	std::ofstream file("route.txt");
	for (auto i : route)
		file << i.x << " " << i.y << std::endl;
	file.close();
	file.open("length.txt");
	file << "length= " << route_length;
	file.close();
	divide_xy();
}

std::vector<coordinates> route_methods::getRoute()
{
	return route;
}

double route_methods::getRouteLength()
{
	return route_length;
}

route_methods::route_methods(coordinates depart, const std::string& file_name)
{
	this->depart = depart;
	this->route = {};
	this->route_length = 0;
	file_input(file_name);
}

route_methods::route_methods(coordinates depart, const std::vector<coordinates>& points)
{
	this->depart = depart;
	this->points = points;
	this->route = {};
	this->route_length = 0;
}

route_methods::route_methods(const std::vector<coordinates>& route, const std::vector<coordinates>& points)
{
	this->depart = route.back();
	this->points = points;
	this->route = route;
	this->route_length = 0;
}

void route_methods::divide_xy()
{
	std::ofstream x_file("route_X.txt"), y_file("route_Y.txt");
	for (auto i : route)
	{
		x_file << i.x << std::endl;
		y_file << i.y << std::endl;
	}
	x_file.close();
	y_file.close();
}