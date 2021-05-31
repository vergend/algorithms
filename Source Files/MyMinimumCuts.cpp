// Code by Michael Zlotnikov 05/2021

#include "MyMinimumCuts.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

using ull = unsigned long long;


class uGraph {
public:
	int n, m;// number of nodes n, and number of edges m
	vector<int> nodes;
	vector<int> counts; // counts[i] = how many nodes have merged with nodes[i], itself included
	vector<pair<int, int>> edges;

	//constructor
	uGraph(int size, vector<pair<int, int>> & inputEdges) {
		n = size;
		nodes.resize(n);
		counts.resize(n);
		for (int i = 0; i < n; i++) { // initialize nodes and counts
			nodes[i] = i;
			counts[i] = 1;
		}
		m = inputEdges.size();
		edges = inputEdges; // store edges
	}
	int findNode(int x) {
		int i = x, j ;
		while (nodes[i] != i) { // find main node in association
			i = nodes[i];
		}
		while (nodes[x] != x) { // remap all intermediate nodes to main node
			j = nodes[x];
			nodes[x] = i;
			x = j;
		}
		return i;
	}
	void collapseEdge() {
		int e, x, y;
		if (n > 2) {
			bool collapsed = false;
			while (!collapsed) {
				e = rand() % m; // rand()%m produces a slightly non-uniform distribution, but good enough for our purpose
				x = findNode(edges[e].first);
				y = findNode(edges[e].second);
				if (x != y) {
					if (counts[x] < counts[y]) {
						counts[y] += counts[x];
						counts[x] = 0;
						nodes[x] = y;
					} else {
						counts[x] += counts[y];
						counts[y] = 0;
						nodes[y] = x;
					}
					n--;
					collapsed = true;
				}
				// remove consumed edge in O(1) time
				// do not actually delete the edge, to keep it for next iteration
				swap(edges[e], edges[m - 1]);
				m--;
			}
		}
	}
	void removeSelfLoopEdges() {
		int x, y;
		for (int e = m - 1; e >= 0; e--) {
			x = findNode(edges[e].first);
			y = findNode(edges[e].second);
			if (x == y) { // remove self-loop edge
				swap(edges[e], edges[m - 1]);
				m--;
			}
		}
	}
};

ull MyMinimumCuts(int size, vector<pair<int, int>> & inputEdges) {
	ull count = UINT_MAX;
	srand(time(NULL));
	uGraph G(size, inputEdges);
	// 1000 iterations as placeholder, >(size-1)/size success probability after size*size*log(size) iterations
	for (int i = 0; i < 1000; i++) { 
		G.n = size;// refresh graph
		G.m = inputEdges.size();
		for (int i = 0; i < size; i++) { // initialize nodes and counts
			G.nodes[i] = i;
			G.counts[i] = 1;
		}
		while (G.n > 2) {
			G.collapseEdge();// collapse edges until 2 nodes left
		}
		G.removeSelfLoopEdges(); // remove any self loop edges from each node
		if (G.m < count) {
			count = G.m; // record smallest number of edges to cut
		}
		/*if (i % 100 == 0) {
			cout << i << "/" << 1000 <<" min found: "<< count << endl;
		}*/
	}
	return count;
}
