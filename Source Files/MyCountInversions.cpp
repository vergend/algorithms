// Code by Michael Zlotnikov 05/2021

#include "MyMergeSort.h"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using my_type = int;
using ull = unsigned long long;

ull MyCountInversionsWork(vector<my_type> & vec, vector<my_type> & work, int l, int r) {
	if (r - l < 2) { return 0; }
	else if (r - l == 2) {
		if (vec[l] > vec[l + 1]) {
			swap(vec[l], vec[l + 1]);
			return 1;
		}
		return 0;
	}
	int m = (l + r) / 2;
	ull count = 0;
	count += MyCountInversionsWork(work, vec, l, m);
	count += MyCountInversionsWork(work, vec, m, r);
	int i = l, j = m, c = l;
	while (c < r) {
		if (i < m && j < r) {
			if (work[i] > work[j]) {
				vec[c] = work[j];
				j++;
				count += m - i;
			}
			else {
				vec[c] = work[i];
				i++;
			}
		}
		else if (i == m) {
			vec[c] = work[j];
			j++;
		}
		else {
			vec[c] = work[i];
			i++;
		}
		c++;
	}
	return count;
}

ull MyCountInversions(vector<my_type> & vec) {
	using my_type = int;
	vector<my_type> work = vec;
	return MyCountInversionsWork(vec, work, 0, vec.size());
}