// Code by Michael Zlotnikov 05/2021

#include "MyKnapsack.h"

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


unsigned long long MyKnapsackWork(vector<pair<unsigned long long, unsigned long long>> & valAndWeights, pair<unsigned long long , unsigned long long> posAndCapacity) {
	unsigned long long out=0;
	static map< pair<unsigned long long, unsigned long long>, unsigned long long > m;
	auto it=m.find(posAndCapacity);
	if (it == m.end()) {
		if (valAndWeights[posAndCapacity.first].second > posAndCapacity.second) {
			if (posAndCapacity.first > 0) {
				out = MyKnapsackWork(valAndWeights, make_pair(posAndCapacity.first-1,posAndCapacity.second));
			}
		} else {
			if (posAndCapacity.first == 0) {
				out = valAndWeights[0].first;
			} else {
				out = max(MyKnapsackWork(valAndWeights, make_pair(posAndCapacity.first - 1, posAndCapacity.second)),
					valAndWeights[posAndCapacity.first].first+MyKnapsackWork(valAndWeights, make_pair(posAndCapacity.first - 1, posAndCapacity.second - valAndWeights[posAndCapacity.first].second)));
			}
		}
		m[posAndCapacity] = out;
	} else {
		out = it->second;
	}
	return out;
}


unsigned long long MyKnapsack(vector<pair<unsigned long long, unsigned long long>> & valAndWeights, unsigned long long capacity) {
	return MyKnapsackWork(valAndWeights, make_pair(valAndWeights.size()-1,capacity));
}