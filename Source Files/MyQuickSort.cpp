// Code by Michael Zlotnikov 05/2021

#include "MyQuickSort.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;
using my_type = int;
using ull = unsigned long long;

ull MyQuickSortWork(vector<my_type> & vec, int l, int r) {
	if (r - l < 2) { return 0; }
	else if (r - l == 2) {
		if (vec[l] > vec[l + 1]) {
			swap(vec[l], vec[l + 1]);
		}
		return 1;
	}
	// rand()%x produces a slightly non-uniform distribution, but good enough for our purpose
	swap(vec[l + rand() % (r-l)], vec[l]); 
	int i = l + 1, j = l + 1;
	while (j < r) {
		if (vec[j] < vec[l]) {
			swap(vec[i], vec[j]);
			i++;
		}
		j++;
	}
	swap(vec[l], vec[i-1]);
	ull count = r - l - 1; // number of comparisons during current iteration
	count += MyQuickSortWork(vec, l, i-1);
	count += MyQuickSortWork(vec, i, r);
	return count;
}

ull MyQuickSort(vector<my_type> & vec) {
	srand(time(NULL));
	return MyQuickSortWork(vec,0,vec.size());
}