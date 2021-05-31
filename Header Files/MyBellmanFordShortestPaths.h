// Code by Michael Zlotnikov 05/2021

#pragma once
#include <vector>

class bellmanFordGraph {
public:
	int n; // number of nodes
	int flip; //current distances vector index
	bool negativeWeightCycle; //whether a negative overall weight cycle is present
	std::vector<std::tuple<int, int, int>> edgesInput; // edges in the graph
	std::vector<std::vector<int>> distances;// keeping track of distances accumulated so far
	bellmanFordGraph(int , std::vector<std::tuple<int, int, int>>& );
	void initialize(int);
	void bellmanFordIterate();
};


unsigned long long MyBellmanFordShortestPaths(int, std::vector<std::tuple<int, int, int>>&);