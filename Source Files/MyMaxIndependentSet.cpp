// Code by Michael Zlotnikov 05/2021

#include "MyMaxIndependentSet.h"

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;


string MyMaxIndependentSet(vector<int> & vec) {
	vector<int> work(vec.size());
	work[0] = vec[0];
	work[1] = max(vec[0], vec[1]);
	for (int i = 2; i < vec.size(); i++) {
		work[i] = max(work[i-1], work[i - 2]+vec[i]);
	}
	set<int> s;
	int i = vec.size() - 1;
	while (i >= 2) {
		if (work[i - 1] >= work[i - 2] + vec[i]) {
			i--;
		} else {
			s.emplace(i);
			i--; i--;
		}
	}
	if (i == 0) { s.emplace(0); }
	else if (i == 1) {
		if (vec[1] > vec[0]) {
			s.emplace(1);
		} else {
			s.emplace(0);
		}
	}
	vector<int> test{ 1, 2, 3, 4, 5, 6 };
	string out = "";
	for (int j = 0; j < test.size(); j++) {
		if (s.count(test[j]-1) > 0) {
			out += '1';
		} else {
			out += '0';
		}
	}
	return out;
}