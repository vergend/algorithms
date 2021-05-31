// Code by Michael Zlotnikov 05/2021

#include "MyRandomSelect.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;
using my_type = int;
using ull = unsigned long long;

int MyRandomSelectWork(vector<my_type> & vec, int l, int r, int pos) {
	if (r - l < 2) { return vec[pos]; }
	else if (r - l == 2) {
		if (vec[l] > vec[l + 1]) {
			swap(vec[l], vec[l + 1]);
		}
		return vec[pos];
	}
	// rand()%x produces a slightly non-uniform distribution, but good enough for our purpose
	swap(vec[l + rand() % (r - l)], vec[l]);
	int i = l + 1, j = l + 1;
	while (j < r) {
		if (vec[j] < vec[l]) {
			swap(vec[i], vec[j]);
			i++;
		}
		j++;
	}
	swap(vec[l], vec[i - 1]);
	int result;
	if (i - 1 == pos) {
		result = vec[i - 1];
	} else if (i - 1 > pos) {
		result = MyRandomSelectWork(vec, l, i - 1,pos);
	} else {
		result = MyRandomSelectWork(vec, i, r, pos);
	}
	return result;
}

int MyRandomSelect(std::vector<int> & vec, int pos) {
	srand(time(NULL));
	return MyRandomSelectWork(vec, 0, vec.size(), pos);
}