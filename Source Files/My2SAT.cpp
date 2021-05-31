// Code by Michael Zlotnikov 05/2021

#include "MyStronglyConnectedComponents.h"
#include "My2SAT.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>

using namespace std;

int My2SAT(int size, vector<pair<int, int>>& inputEdges) {
	int out = 1;
	dGraph G(size, inputEdges);
	G.DFSloop(); // obtain node finishing times
	G.invDFSloop(); // obtain node leader labels
	for (int i = 0; i < size / 2; ++i) {
		if (G.leader[i] == G.leader[i + size / 2]) {
			out = 0;
			break;
		}
	}
	return out;
}