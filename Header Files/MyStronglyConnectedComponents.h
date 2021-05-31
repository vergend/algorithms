// Code by Michael Zlotnikov 05/2021

#pragma once
#include <vector>
#include <map>

class dGraph {
public:
	int n, t, s;// number of nodes n, tracker of finishing time t, tracker of leader nodes s
	std::vector<std::vector<int>> outgoingEdges; // directed edges from node i to nodes outgoingEdges[i][j] for appropriate j
	std::vector<std::vector<int>> ingoingEdges; // directed edges from nodes outgoingEdges[i][j] for appropriate j to node i
	std::vector<int> visited; // toggle if node has been visited during depth first search
	std::vector<int> finishingTime; // finishing time for each node during first depth first search traversal
	std::vector<int> leader; // keep track of leader nodes during second depth first search traversal

	std::map<int, int> leaderGroupCounts;// will hold number of member nodes for each leader node
	std::vector<int> groupCounts; // will hold all group sizes in decreasing order

	dGraph(int , std::vector<std::pair<int, int>> & );
	void DFS(int i);
	void DFSloop();
	void invDFS(int i);
	void invDFSloop();
	void countGroupSizes();
};

unsigned long long MyStronglyConnectedComponents(int, std::vector<std::pair<int, int>>&);