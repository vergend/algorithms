// Code by Michael Zlotnikov 05/2021

#include "MyBellmanFordShortestPaths.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using ull = unsigned long long;



	bellmanFordGraph::bellmanFordGraph(int size, vector<tuple<int, int, int>>& edges) {
		n = size;
		vector<int> dist(n, 0);
		distances.push_back(dist);
		distances.push_back(dist);
		edgesInput = edges;
	}
	void bellmanFordGraph::initialize(int fromNode) {
		for (int i = 0; i < n; i++) {
			distances[0][i] = INT_MAX/4;
			distances[1][i] = INT_MAX/4;
		}
		distances[0][fromNode] = 0;
		distances[1][fromNode] = 0;
		negativeWeightCycle = false;
	}
	void bellmanFordGraph::bellmanFordIterate() {
		int cnt = 0;
		bool change=true;
		flip = 0;
		while(change==true && cnt<n){
			flip = (flip + 1) % 2;
			change = false;
			for (int i = 0; i < edgesInput.size(); i++) {
				distances[flip][get<2>(edgesInput[i])] = min( distances[flip][get<2>(edgesInput[i])] , min( distances[(flip+1)%2][get<2>(edgesInput[i])] , distances[(flip + 1) % 2][get<1>(edgesInput[i])]+ get<0>(edgesInput[i]) ) );
				if (distances[flip][get<2>(edgesInput[i])] < distances[(flip + 1) % 2][get<2>(edgesInput[i])]) {
					change = true;
				}
			}
			if(change){
				cnt++;
			}
		}
		if (cnt == n) {
			negativeWeightCycle = true;
		}
	}



ull MyBellmanFordShortestPaths(int size, vector<tuple<int, int, int>>& edges) {
	bellmanFordGraph G(size, edges);
	G.initialize(0);
	G.bellmanFordIterate();
	if (G.negativeWeightCycle) {
		cout << "Negative weight cycle detected!" << endl;
		return 0;
	}
	return G.distances[G.flip][size - 1];
}