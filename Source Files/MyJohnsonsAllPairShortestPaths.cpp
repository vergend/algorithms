// Code by Michael Zlotnikov 05/2021

#include "MyDijkstrasShortestPaths.h"
#include "MyBellmanFordShortestPaths.h"
#include "MyJohnsonsAllPairShortestPaths.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


int MyJohnsonsAllPairShortestPaths(int size, vector<tuple<int, int, int>>& edges) {
	vector<tuple<int, int, int>>  augmentedEdges = edges;
	for (int i = 0; i < size; i++) {
		augmentedEdges.push_back(make_tuple(0,i,size));
	}
	bellmanFordGraph Gbf(size + 1, augmentedEdges);
	Gbf.initialize(size);
	Gbf.bellmanFordIterate();
	if (Gbf.negativeWeightCycle) {
		cout << "Negative weight cycle detected!" << endl;
		return 0;
	}
	augmentedEdges = edges;
	for (int i = 0; i < augmentedEdges.size(); i++) {
		get<0>(augmentedEdges[i]) += Gbf.distances[Gbf.flip][get<1>(augmentedEdges[i])];
		get<0>(augmentedEdges[i]) -= Gbf.distances[Gbf.flip][get<2>(augmentedEdges[i])];
	}
	int shortest=INT_MAX;
	dijkstraGraph Gd(size , augmentedEdges);
	for (int i = 0; i < size; i++) {
		Gd.initialize(i);
		Gd.dijkstraIterate();
		for (int j = 0; j < size; j++) {
			Gd.distances[j] -= Gbf.distances[Gbf.flip][i];
			Gd.distances[j] += Gbf.distances[Gbf.flip][j];
			if (i != j && Gd.distances[j] < shortest) {
				shortest = Gd.distances[j];
			}
		}
	}
	return shortest;
}