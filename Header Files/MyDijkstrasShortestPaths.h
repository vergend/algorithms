// Code by Michael Zlotnikov 05/2021

#pragma once
#include <vector>

using weight_type = int; //weight type



class myHeap {
public:
	std::vector<std::tuple<weight_type, int, int>> tree;
	std::vector<int> position;
	void initialize(int);
	void bubbleUp(int);
	void bubbleDown(int);
	void insert(std::tuple<weight_type, int, int> & );
	std::tuple<weight_type, int, int> extractTop();
};


class dijkstraGraph {
public:
	int n;
	std::vector<std::vector<std::tuple<weight_type, int, int>>> nodes;// nodes[i] contains a vector of edges originating at node i
	std::vector<weight_type> distances;// keeping track of distances from origin node
	std::vector<int> X; // keeping track of nodes already visited
	myHeap h; // heap to determine the next minimum distance node
	dijkstraGraph(int , std::vector<std::tuple<weight_type, int, int>>& );
	void initialize(int );
	void dijkstraIterate();
};


unsigned long long MyDijkstrasShortestPaths(int, std::vector<std::tuple<weight_type, int, int>>& );