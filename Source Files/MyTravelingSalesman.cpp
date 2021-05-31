// Code by Michael Zlotnikov 05/2021

#include "MyTravelingSalesman.h"
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


unsigned long long MyTravelingSalesman(vector<vector<double>>& d) {
	int n = d.size();
	n = 5;
	if ( n > 27) { return -1; }//allow problems up to size 27 cities, return error code otherwise
	//create bit maps to check whether each city was visited before
	vector<unsigned int> loc(n);
	loc[0] = 2*2*2*2*2;
	for (int i = 1; i < n; i++) {
		loc[i] = loc[i - 1] * 2;
		//bitset<32> y(loc[i]);
		//cout << y << endl;
	}
	unsigned int maskNumber = 31; // 00000000000000000000000000011111 mask to select the first 5 bits from 32 bits in an integer
	unsigned int maskCities = ~maskNumber; // 11111111111111111111111111100000 mask to select boolean for whether city 1 through 27 was visited
	unsigned int p,tp;
	vector< unordered_map<unsigned int, double> > m(2);
	unordered_map<unsigned int, double>::iterator itm;
	int c = 0;// flip parameter between two different hashmaps on each iteration
	m[c][loc[0]+0] = 0.;// set first city as visited with zero distance travelled
	stack < unsigned int > st[2];
	st[c].push(loc[0] + 0);
	cout << "Considered all relevant paths with visited number of cities so far: ";
	for (int len = 2; len <= n; len++) {
		cout << len << ",";
		while (st[c].size() > 0) {
			p = st[c].top();
			st[c].pop();
			for (unsigned int i = 1; i < n;i++) {
				if((p&(loc[i]))==0){ // if city i has not been visited on this trip so far
					tp = ((p + loc[i])&(maskCities))+i; // create new label with city i switched to "visited", and i selected as last visited city
					itm = m[(c + 1) % 2].find(tp);
					if (itm == m[(c + 1) % 2].end()) {
						st[(c + 1) % 2].push(tp);
						m[(c + 1) % 2][tp] = m[c].find(p)->second + d[p&maskNumber][i];
					} else {
						if (m[c].find(p)->second + d[p&maskNumber][i] < m[(c + 1) % 2].find(tp)->second) {
							m[(c + 1) % 2].find(tp)->second = m[c].find(p)->second + d[p&maskNumber][i];
						}
					}
				}
			}
		}
		m[c].clear();
		c = (c + 1) % 2;
	}
	cout << endl;
	unsigned long long out = UINT_MAX;
	while (st[c].size() > 0) {
		p = st[c].top();
		st[c].pop();
		if (m[c].find(p)->second + d[0][p&maskNumber] < out) {
			out = m[c].find(p)->second + d[0][p&maskNumber];
		}
	}
	return out;
}