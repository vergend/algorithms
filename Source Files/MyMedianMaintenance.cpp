// Code by Michael Zlotnikov 05/2021

#include "MyMedianMaintenance.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int MyMedianMaintenance(std::vector<int>& vec) {
	int accumulate = 0,tmp;
	priority_queue<int, vector<int>, less<int>>    lower;// largest element at the top (standard)
	priority_queue<int, vector<int>, greater<int>> higher;// smallest element at the top
	//cout << endl << endl;
	for (int i = 0; i < vec.size(); i++) {
		if (lower.empty() && higher.empty()) {
			lower.emplace(vec[i]);
		} else if (higher.empty()) {
			tmp = lower.top();
			lower.pop();
			lower.emplace(min(tmp, vec[i]));
			higher.emplace(max(tmp, vec[i]));
		} else {
			if (vec[i] < lower.top()) {
				tmp = lower.top();
				lower.pop();
				lower.emplace(vec[i]);
			} else if (vec[i] > higher.top()) {
				tmp = higher.top();
				higher.pop();
				higher.emplace(vec[i]);
			} else { 
				tmp = vec[i];
			}
			if (lower.size() <= higher.size()) {
				lower.emplace(tmp);
			} else {
				higher.emplace(tmp);
			}
		}
		accumulate += lower.top();
		//cout << lower.top() << ",";
	}
	//cout << endl << endl;
	return accumulate % 10000; // return accumulated median modulo 10000
}