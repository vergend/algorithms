// Code by Michael Zlotnikov 05/2021

#include "My2SUM.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

unsigned long long My2SUM(vector<long long> & vec) {
	map<long long, int>m;
	map<long long, int>::iterator it;
	for (int i = 0; i < vec.size(); i++) {
		it = m.find(vec[i]);
		if (it != m.end()) {
			it->second++;
		} else {
			m[vec[i]] = 1;
		}
	}
	set<int> s;
	for (int i = 0; i < vec.size(); i++) {
		if (i % 10000 == 9999) {
			cout << "Checked: " << i << endl;
		}
		for (int j = -10000; j <= 10000; j++) {
			if (j - vec[i] == vec[i] && m[vec[i]]>1) {
				s.emplace(j);
			} else {
				if (m.count(j - vec[i]) > 0) {
					s.emplace(j);
				}
			}
		}
	}
	return s.size();
}