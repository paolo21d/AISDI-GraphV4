#include <iostream>
#include <ctime>
#include "Graph.h"

using namespace std;
int main() {
	Graph g;
	g.inputGraphFromFile("graf1.txt");
	//g.inputGraphLab();
	g.printGraph();
	clock_t begin = clock();
	g.getBridges();
	clock_t end = clock();
	cout << endl << "Czas obliczania: " << double(end - begin) / CLOCKS_PER_SEC << endl;
	system("pause");
}