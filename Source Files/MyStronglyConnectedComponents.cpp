// Code by Michael Zlotnikov 05/2021

#include "MyStronglyConnectedComponents.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>

using namespace std;

using ull = unsigned long long;


	dGraph::dGraph(int size, vector<pair<int, int>> & inputEdges) {
		n = size;
		outgoingEdges.resize(n);
		ingoingEdges.resize(n);
		visited.resize(n);
		visited.assign(n,false);
		finishingTime.resize(n);
		leader.resize(n);
		for (int i = 0; i < inputEdges.size(); i++) {
			outgoingEdges[inputEdges[i].first].push_back(inputEdges[i].second);
			ingoingEdges[inputEdges[i].second].push_back(inputEdges[i].first);
		}
	}
	void dGraph::DFS(int i) {
		visited[i] = true;
		for (int j = 0; j < outgoingEdges[i].size(); ++j) {
			if (!visited[outgoingEdges[i][j]]) {
				DFS(outgoingEdges[i][j]);
			}
		}
		t++;
		finishingTime[t-1] = i;
	}
	void dGraph::DFSloop() {
		t = 0;// zero time
		for (int i = n - 1; i >= 0; i--) {
			if(!visited[i]){
				DFS(i);
			}
		}
	}
	void dGraph::invDFS(int i) {
		visited[i] = false;
		leader[i] = s;
		for (int j = 0; j < ingoingEdges[i].size(); ++j) {
			if (visited[ingoingEdges[i][j]]) {
				invDFS(ingoingEdges[i][j]);
			}
		}
	}
	void dGraph::invDFSloop() {
		for (int i = n - 1; i >= 0; i--) {
			if(visited[finishingTime[i]]){
				s = finishingTime[i];
				invDFS(s);
			}
		}
	}
	void dGraph::countGroupSizes() {
		for (int i = 0; i < n; i++) {
			if (leaderGroupCounts.count(leader[i]) == 0) {
				leaderGroupCounts[leader[i]] = 1;
			} else {
				leaderGroupCounts[leader[i]]++;
			}
		}
		for (auto it = leaderGroupCounts.begin(); it != leaderGroupCounts.end(); ++it) {
			groupCounts.push_back(it->second);
		}
		sort(groupCounts.begin(), groupCounts.end(), greater<>());
	}

ull MyStronglyConnectedComponents( int size, vector<pair<int, int>> & inputEdges) {
	dGraph G(size, inputEdges);
	G.DFSloop(); // obtain node finishing times
	G.invDFSloop(); // obtain node leader labels
	G.countGroupSizes();
	// print largest five group sizes
	cout << "Sizes of five largest strongly connected components: " ;
	int c; for (c = 0; c < min(5, (int)G.groupCounts.size()); c++) {
		cout << G.groupCounts[c] << ",";
	}
	for (; c < 5; c++) {
		cout << 0 << ",";
	}
	cout << endl;
	return (ull)G.groupCounts.size();
}
