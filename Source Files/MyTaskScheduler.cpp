// Code by Michael Zlotnikov 05/2021

#include "MyTaskScheduler.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

std::pair<long long, long long> MyTaskScheduler(vector<pair<int, int>> & vec) {
	map<int, multiset<pair<int, int>>> wml;
	map<int, multiset<pair<int, int>>>::iterator wmlIt;
	map<double, multiset<pair<int, int>>> wdl;
	map<double, multiset<pair<int, int>>>::iterator wdlIt;
	for (int i = 0; i < vec.size(); i++) {
		wmlIt = wml.find(vec[i].first - vec[i].second);
		if (wmlIt == wml.end()) {
			multiset<pair<int, int>> s{ vec[i] };
			wml[vec[i].first - vec[i].second] = s;
		} else {
			wmlIt->second.emplace(vec[i]);
		}
		wdlIt = wdl.find(((double)vec[i].first)/vec[i].second);
		if (wdlIt == wdl.end()) {
			multiset<pair<int, int>> s{ vec[i] };
			wdl[((double)vec[i].first) / vec[i].second] = s;
		}
		else {
			wdlIt->second.emplace(vec[i]);
		}
	}
	multiset<pair<int, int>>::iterator it;
	long long wmlLsoFar = 0, wmlCsum = 0;
	wmlIt = wml.end();
	while (wmlIt != wml.begin()) {
		wmlIt--;
		it = wmlIt->second.end();
		while (it != wmlIt->second.begin()) {
			it--;
			wmlLsoFar += it->second;
			wmlCsum += wmlLsoFar*(it->first);
		}
	}
	long long wdlLsoFar = 0, wdlCsum = 0;
	wdlIt = wdl.end();
	while (wdlIt != wdl.begin()) {
		wdlIt--;
		it = wdlIt->second.end();
		while (it != wdlIt->second.begin()) {
			it--;
			wdlLsoFar += it->second;
			wdlCsum += wdlLsoFar * (it->first);
		}
	}
	return make_pair(wmlCsum, wdlCsum);
}