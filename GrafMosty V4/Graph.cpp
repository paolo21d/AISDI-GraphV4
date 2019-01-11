#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

/*bool Graph::delFunc(const unsigned &d) {
return d==removeElement;
}*/

Graph::Graph() {
	vertex = 0;
	edge = 0;
	adjList = nullptr;
}

Graph::~Graph() {
	if (adjList != nullptr)
		delete[] adjList;
}

void Graph::inputGraph() {
	cin >> vertex >> edge;
	adjList = new list<unsigned>[vertex]; //zaalokowanie pamięci na listę sąsiedztwa
	unsigned v1, v2;
	for (unsigned i = 0; i < edge; ++i) { //wczytanie krawedzi do list sasiedztwa
		cin >> v1 >> v2;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
		edges.push_back(make_pair(v1, v2));
	}

	/*for (unsigned i = 0; i < vertex; ++i) { //posortowanie list sąsiedztwa
	sort(adjList[i].begin(), adjList[i].end());
	}*/
}

bool Graph::inputGraphFromFile(string src) {
	fstream file;
	file.open(src, ios::in);
	if (!file.good())
		return false;

	file >> vertex;
	adjList = new list<unsigned>[vertex]; //zaalokowanie pamięci na listę sąsiedztwa
	unsigned v1, v2;
	while (file.good()) {
		file >> v1 >> v2;
		if (file.fail()) break; //sprawdzenie czy to juz byl koniec danych
		++edge;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
		edges.push_back(make_pair(v1, v2));
	}

	/*for (unsigned i = 0; i < vertex; ++i) { //posortowanie list sąsiedztwa
	sort(adjList[i].begin(), adjList[i].end());
	}*/

	file.close();
	return true;
}

void Graph::inputGraphLab() {
	cin >> vertex;
	adjList = new list<unsigned>[vertex]; //zaalokowanie pamięci na listę sąsiedztwa
	unsigned v1, v2;
	unsigned e = 0;
	while (!cin.eof()) {
		cin >> v1 >> v2;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
		edges.push_back(make_pair(v1, v2));
		++e;
	}
	edge = e;
}

bool Graph::checkConnectivity(unsigned delV1, unsigned delV2) {
	vector<bool>visited;
	unsigned v, u, vc = 0;
	for (int i = 0; i < vertex; ++i) visited.push_back(false);
	visited[delV1] = true;
	visited[delV2] = true;
	stack<unsigned> s;

	if (vertex == 0) return true; //graf pusty traktujemy jako spojny

	s.push(0);
	visited[0] = true;
	while (!s.empty()) {
		v = s.top();
		s.pop();
		++vc;
		for (auto it = adjList[v].begin(); it != adjList[v].end(); ++it) {
			u = *it;
			if (!visited[u]) {
				visited[u] = true;
				s.push(u);
			}
		}
	}

	if (vc == vertex) return true;
	else return false;
}

void Graph::getBridges() {
	unsigned delV1, delV2, cn;
	for (auto i = 0; i < edges.size(); ++i) {
		delV1 = edges[i].first;
		delV2 = edges[i].second;
		cn = getQuantityOfComponents(delV1, delV2);
		if(cn>1) cout << "Most rozlegly: " << delV1 << " " << delV2 << endl;
		//if(!checkConnectivity(delV1, delV2)) cout << "Most rozlegly: " << delV1 << " " << delV2 << endl;
	}
}

int Graph::getQuantityOfComponents(unsigned delV1, unsigned delV2) {
	int cn = 0; // Zerujemy licznik spójnych składowych
	static unsigned v, u;
	//static vector<bool> visited(vertex);
	static vector<bool> visited;
	stack<unsigned> S;
	for (unsigned i = 0; i < vertex; ++i) visited.push_back(false); //zerowanie listy odwiedzonych wierzcholkow
	//for (auto i = 0; i < vertex; ++i) visited[i] = false;
	visited[delV1] = true;
	visited[delV2] = true;

	for (unsigned i = 0; i < vertex; ++i)
		if (!visited[i])                // Szukamy nieodwiedzonego jeszcze wierzchołka
		{
			cn++;                  // Zwiększamy licznik składowych
			if (cn > 1) return cn;
			S.push(i);             // Na stosie umieszczamy numer bieżącego wierzchołka
			visited[i] = true;             // i oznaczamy go jako odwiedzonego i ponumerowanego
			while (!S.empty())      // Przechodzimy graf algorytmem DFS
			{
				v = S.top();         // Pobieramy wierzchołek
				S.pop();             // Usuwamy go ze stosu
									 // Przeglądamy sąsiadów wierzchołka v
				for (auto it = adjList[v].begin(); it != adjList[v].end(); ++it) {
					u = *it;
					if (!visited[u]) {
						S.push(u);
						visited[u] = true;
					}
				}
			}
		}

	return cn;
}

void Graph::printGraph() {
	cout << "Vertex: " << vertex << "\tEdge: " << edge << endl;
	for (int i = 0; i < vertex; ++i) {
		cout << "V " << i << ":\t";
		//for (int x = 0; x < adjList[i].size(); ++x)
		//	cout << adjList[i][x] << " ";
		for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
}
