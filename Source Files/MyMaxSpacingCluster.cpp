// Code by Michael Zlotnikov 05/2021

#include "MyMaxSpacingCluster.h"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using my_type = int;

class dset {
public:
	int n;//number of clusters
	vector<int> parent;//keep track of clusters
	vector<int> rank;//keep track of node ranks
	dset(int size) {
		n = size;
		parent.resize(n);
		rank.resize(n);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	int find(int x) {
		int i = x, j;
		while (parent[i] != i) {
			i = parent[i];
		}
		while (parent[x] != x) {
			j = parent[x];
			parent[x] = i;
			x = j;
		}
		return i;
	}
	void merge(int x, int y) {
		x = find(x);
		y = find(y);
		if(x!=y){
			if (rank[x] >= rank[y]) {
				parent[y] = x;
				if (rank[x] == rank[y]) {
					rank[x]++;
				}
			} else {
				parent[x] = y;
			}
			n--;
		}
	}
};

int MyMaxSpacingCluster(int k, int size, vector<tuple<int, int, int>> & edges) {
	sort(edges.begin(), edges.end());
	auto it = edges.begin();
	dset ds(size);
	while (ds.n > k && it!=edges.end()) {
		ds.merge(get<1>(*it), get<2>(*it));
		it++;
	}
	while (it != edges.end() && ds.find(get<1>(*it))== ds.find(get<2>(*it))) {
		it++;
	}
	if (it == edges.end()) { return 0; }
	return get<0>(*it);
}

int MyMaxSpacingClusterBig(int spacing, int size, vector<vector<int>> & nodes) {
	dset ds(size);
	int dif;
	cout << "progress out of "<<nodes.size()<<":"<<endl;
	for (int i = 0; i < nodes.size()-1; i++) {
		for (int j = i + 1; j < nodes.size(); j++) {
			dif = 0;
			for (int l = 0; l < nodes[0].size(); l++) {
				if (nodes[i][l] != nodes[j][l]) {
					dif++;
				}
			}
			if (dif < spacing) {
				ds.merge(i, j);
			}
		}
		if (i % 1000 == 0) {
			cout << i << ",";
		}
	}
	cout << endl;
	return ds.n;
}