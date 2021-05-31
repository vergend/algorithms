// Code by Michael Zlotnikov 05/2021

#include "MyDijkstrasShortestPaths.h"
#include "MyPrimsMinimumSpanningTree.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>
#include <map>

using namespace std;
using weight_type = int; //weight type



class primGraph {
public:
	int n;
	vector<vector<tuple<weight_type, int, int>>> nodes;// nodes[i] contains a vector of edges originating at node i
	long long totalCost;// keeping track of total cost of edges in the minimum spanning tree
	vector<int> X; // keeping track of nodes already visited
	myHeap h; // heap to determine the next minimum distance node

	primGraph(int size, vector<tuple<weight_type, int, int>>& edges) {
		n = size;
		totalCost = 0;
		nodes.resize(n);
		X.resize(n, 0);
		for (int i = 0; i < edges.size(); i++) {
			nodes[get<1>(edges[i])].push_back(edges[i]);
			swap(get<1>(edges[i]), get<2>(edges[i]));
			nodes[get<1>(edges[i])].push_back(edges[i]);
		}
		h.initialize(n);
		X[0] = 1;
		for (int i = 0; i < nodes[0].size(); i++) {
			h.insert(nodes[0][i]);
		}
	}

	void primIterate() {
		int s;
		tuple<weight_type, int, int> top;
		while (h.tree.size() > 0) {
			top = h.extractTop();
			s = get<2>(top);
			X[s] = 1;
			totalCost += get<0>(top);
			for (int i = 0; i < nodes[s].size(); i++) {
				if (X[get<2>(nodes[s][i])] == 0) {
					h.insert(nodes[s][i]);
				}
			}
		}
	}

};

long long MyPrimsMinimumSpanningTree(int size, vector<tuple<int, int, int>> & edges) {
	primGraph G(size, edges);
	G.primIterate();
	return G.totalCost;
}