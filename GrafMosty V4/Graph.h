#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <utility>
class Graph
{
	unsigned vertex; //ilosc wierzcholkow
	unsigned edge; //ilosc krawedzi
				   //std::vector<unsigned> *adjList; //lista s�siedztwa
	std::list<unsigned> *adjList;
	std::vector<std::pair<unsigned, unsigned>> edges;

	//unsigned removeElement;
	//bool delFunc(const unsigned &d);
public:
	Graph();
	~Graph();

	void inputGraph(); //wczytanie grafu z konsoli
	bool inputGraphFromFile(std::string src); //wczytanie grafu z pliku (plik nie moze byc zakonczony enterem)
	void inputGraphLab(); //wczytywanie grafu na labie
	bool checkConnectivity(unsigned delV1, unsigned delV2);
	void getBridges(); //wypisanie mostow rozleglych grafu
	int getQuantityOfComponents(unsigned delV1, unsigned delV2);
	void printGraph();
};

#endif // !GRAPH_H