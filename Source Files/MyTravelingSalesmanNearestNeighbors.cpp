// Code by Michael Zlotnikov 05/2021

#include "MyTravelingSalesmanNearestNeighbors.h"
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <array>
#include <stack>
#include <algorithm>
#include <time.h>
#include <bitset>

using namespace std;

unsigned long long MyTravelingSalesmanNearestNeighbors(vector<pair<long double, long double>>& data) {
	int n = data.size(),last=0,next;
	long double fullDistance=0., distanceSQ,minDistanceSQ;
	unsigned long long out = 0;
	if (n < 2) { return out; }
	set<int> unvisited;
	for (int i = 1; i < n; ++i) {
		unvisited.insert(unvisited.end(), i);
	}
	auto it = unvisited.end();
	if(unvisited.size() > 1000){
		cout << "Number of unvisited cities remaining: ";
	}
	while (unvisited.size() > 0) {
		if(unvisited.size()%1000==0){
			cout << unvisited.size() << ","<<endl;
		}
		it = unvisited.end();
		minDistanceSQ = numeric_limits<long double>::max();
		while(it!=unvisited.begin()) {
			--it;
			distanceSQ = (data[last].first - data[*it].first)*(data[last].first - data[*it].first) + (data[last].second - data[*it].second)*(data[last].second - data[*it].second);
			if (distanceSQ <= minDistanceSQ) {
				minDistanceSQ = distanceSQ;
				next = *it;
			}
		}
		fullDistance += sqrt(minDistanceSQ);
		last = next;
		unvisited.erase(last);
	}
	fullDistance += sqrt((data[last].first - data[0].first)*(data[last].first - data[0].first) + (data[last].second - data[0].second)*(data[last].second - data[0].second));
	out = floor(fullDistance);
	return out;
}