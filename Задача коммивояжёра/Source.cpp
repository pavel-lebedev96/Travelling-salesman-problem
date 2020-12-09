#include "clusters_methods.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <locale.h>
std::chrono::time_point<std::chrono::system_clock> start, end;
void choice_clastering()
{
	int clustersNum;
	std::cout << "Количество кластеров:" << std::endl;
	std::cin >> clustersNum;
	clusterAnalysis cA("input.txt");
	
	cA.clustering(clustersNum);
	
	cA.file_output();
	system("pause");
	exit(0);
}
void choice_greedy_algorithm()
{
	greedy_algorithm ga({ 0,0 }, "input.txt");
	
	start = std::chrono::system_clock::now();
	ga.make_route(true);
	end = std::chrono::system_clock::now();
	
	ga.file_output();

}
void choice_brute_force()
{
	brute_force bf({ 0,0 }, "input.txt");
	
	start = std::chrono::system_clock::now();
	bf.make_route();
	end = std::chrono::system_clock::now();
	
	bf.file_output();
}
void choice_clastering_and_bf()
{
	int clustersNum;
	std::cout << "Количество кластеров:" << std::endl;
	std::cin >> clustersNum;
	clustersMethod cm({ 0,0 }, "input.txt", clustersNum);
	
	start = std::chrono::system_clock::now();
	cm.make_route();
	end = std::chrono::system_clock::now();
	
	cm.file_output();
}
int main()
{
	setlocale(LC_ALL, "rus");
	char choice, clustersNum;
	do
	{
		std::cout << "Кластеризация - 1" << std::endl;
		std::cout << "Построение маршрутов  - 2" << std::endl;
		choice = _getch();
	} while (choice != '1' && choice != '2');
	system("cls");
	if (choice == '1')
		choice_clastering();
	do
	{
		std::cout << "Метод ближайшего соседа - 1" << std::endl;
		std::cout << "Полный перебор  - 2" << std::endl;
		std::cout << "Кластеризация и полный перебор  - 3" << std::endl;
		choice = _getch();
	} while (choice != '1' && choice != '2' && choice != '3');
	system("cls");
	switch (choice)
	{
	case '1':
		choice_greedy_algorithm();
		break;
	case '2':
		choice_brute_force();
		break;
	case '3':
		choice_clastering_and_bf();
		break;
	}
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
		(end - start).count();
	time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "Time " << elapsed_seconds << "s\n";
	system("pause");
	exit(0);
}