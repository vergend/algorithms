// Code by Michael Zlotnikov 05/2021

#include "MyDijkstrasShortestPaths.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using ull = unsigned long long;
using weight_type = int; //weight type




	void myHeap::initialize(int n) {
		position.resize(n);
		for (int i = 0; i < n; i++) {
			position[i] = -1;
		}
		tree.clear();
	}
	void myHeap::bubbleUp(int s) {
		int p = (s - 1) / 2;
		swap(position[get<2>(tree[s])], position[get<2>(tree[p])]);
		swap(tree[s], tree[p]);
		int pp = (p - 1) / 2;
		if (pp > -1 && get<0>(tree[p]) < get<0>(tree[pp])) {
			bubbleUp(p);
		}
	}
	void myHeap::bubbleDown(int s) {
		int c1 = 2 * s + 1, c2 = 2 * s + 2, c = -1;
		if (c2 < tree.size() && get<0>(tree[c2]) < get<0>(tree[c1])) {
			c = c2;
		} else if (c1 < tree.size()) {
			c = c1;
		}
		if (c > -1 && get<0>(tree[s])> get<0>(tree[c])) {
			swap(position[get<2>(tree[s])], position[get<2>(tree[c])]);
			swap(tree[s], tree[c]);
			bubbleDown(c);
		}
	}
	void myHeap::insert(tuple<weight_type, int, int> & node) {
		if (position[get<2>(node)]>-1) {
			int s = position[get<2>(node)];
			if(get<0>(node) < get<0>(tree[s])){
				int p = (s - 1) / 2;
				tree[s] = node;
				if (get<0>(node) < get<0>(tree[p])) {
					bubbleUp(s);
				}
			}
		} else  {
			tree.push_back(node);
			position[get<2>(node)] = tree.size() - 1;
			if ( get<0>(node) < get<0>(tree[(tree.size() - 2) / 2])) {
				bubbleUp(tree.size() - 1);
			}
		}
	}
	tuple<weight_type, int, int> myHeap::extractTop() {
		tuple<weight_type, int, int> result;
		if(tree.size()>0){
			result = tree[0];
			swap(position[get<2>(tree[0])], position[get<2>(tree[tree.size()-1])]);
			swap(tree[0], tree[tree.size() - 1]);
			position[get<2>(tree[tree.size() - 1])] = -1;
			tree.pop_back();
			bubbleDown(0);
		}
		return result;
	}


	dijkstraGraph::dijkstraGraph(int size, vector<tuple<weight_type, int, int>>& edges) {
		n = size;
		distances.resize(n);
		X.resize(n);
		nodes.resize(n);
		for (int i = 0; i < edges.size(); i++) {
			nodes[get<1>(edges[i])].push_back(edges[i]);
		}
	}

	void dijkstraGraph::initialize(int fromNode) {
		for (int i = 0; i < n; i++) {
			distances[i] = INT_MAX;
			X[i] = 0;
		}
		h.initialize(n);
		X[fromNode] = 1;
		for (int i = 0; i < nodes[fromNode].size(); i++) {
			h.insert(nodes[fromNode][i]);
		}
	}

	void dijkstraGraph::dijkstraIterate() {
		int s;
		tuple<weight_type, int, int> top;
		while (h.tree.size() > 0) {
			top = h.extractTop();
			s = get<2>(top);
			X[s]=1;
			distances[s] =  get<0>(top);
			for (int i = 0; i < nodes[s].size();i++) {
				if (X[get<2>(nodes[s][i])] == 0) {
					top = nodes[s][i];
					get<0>(top) += distances[s];
					h.insert(top);
				}
			}
		}
	}

ull MyDijkstrasShortestPaths(int size, vector<tuple<weight_type, int, int>>& edges) {
	dijkstraGraph G(size, edges);
	G.initialize(0);
	G.dijkstraIterate();
	return G.distances[size-1];
}