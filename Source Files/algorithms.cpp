// Code by Michael Zlotnikov 05/2021
// algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "MyMergeSort.h"
#include "MyCountInversions.h"
#include "MyQuickSort.h"
#include "MyRandomSelect.h"
#include "MyMinimumCuts.h"
#include "MyStronglyConnectedComponents.h"
#include "MyDijkstrasShortestPaths.h"
#include "MyBellmanFordShortestPaths.h"
#include "MyMedianMaintenance.h"
#include "My2SUM.h"
#include "MyTaskScheduler.h"
#include "MyPrimsMinimumSpanningTree.h"
#include "MyMaxSpacingCluster.h"
#include "MyHuffmanCode.h"
#include "MyMaxIndependentSet.h"
#include "MyKnapsack.h"
#include "MyJohnsonsAllPairShortestPaths.h"
#include "MyTravelingSalesman.h"
#include "MyTravelingSalesmanNearestNeighbors.h"
#include "My2SAT.h"

using namespace std;
using my_type = int;
using ull = unsigned long long;


int main()
{
	cout << endl << "----------- MyMergeSort test -----------" << endl;
	int n = 50;
	vector<my_type> vec(n);
	for (int i = 0; i <n; i++) {
		vec[i] = n-i;
	}
	ull res= MyMergeSort(vec);
	for(int i=0;i<n;i++){
		cout << vec[i] <<",";
	}
	cout << endl;
	cout << endl << "----------- MyCountInversions test -----------" << endl;
	vector<my_type> mci{1,3,5,2,4,6};
	res = MyCountInversions(mci);
	cout << "Number of inversions: " << res << endl;
	for (int i = 0; i < mci.size(); i++) {
		cout << mci[i] << ",";
	}
	cout << endl;
	cout << endl << "----------- MyQuickSort test -----------" << endl;
	vector<my_type> mqs{ 2,1,5,6,6,4,8,15,16,8,20,35,3,18 };
	res = MyQuickSort(mqs);
	cout  << "Number of comparisons: " << res << endl;
	for (int i = 0; i < mqs.size(); i++) {
		cout << mqs[i] << ",";
	}
	cout << endl;
	cout << endl << "----------- MyRandomSelect test -----------" << endl;
	vector<my_type> mrs{ 2,1,5,6,6,4,8,15,16,8,20,35,3,18 };
	res = MyRandomSelect(mrs,10);
	cout << "Number at position 10: " << res << endl;

	cout << endl << "----------- MyMinimumCuts test -----------" << endl;
	int size = 5;
	vector<pair<int, int>> MMCedges{make_pair(0,1),make_pair(0,2) ,make_pair(0,3) ,make_pair(1,2) ,make_pair(1,3) ,make_pair(2,3) ,make_pair(3,4) };
	res = MyMinimumCuts(size,MMCedges);
	cout << "Found minimum number of edges to cut: " << res << endl;

	cout <<endl<< "----------- MyStronglyConnectedComponents test -----------" << endl;
	vector<pair<int, int>> MSCCedges{
	make_pair(0,6),make_pair(6,3),make_pair(3,0),make_pair(6,8),make_pair(8,5),make_pair(5,2),make_pair(2,8),make_pair(5,7),make_pair(7,1),make_pair(1,4),make_pair(4,7)
	};
	size = 9;
	res = MyStronglyConnectedComponents(size, MSCCedges);
	cout << "Number of distinct strongly connected components: " << res << endl;

	cout << endl << "----------- MyDijkstrasShortestPaths and MyBellmanFordShortestPaths test -----------" << endl;
	using weight_type = int; //weight type
	size = 4;
	vector<tuple<weight_type, int, int>> MDSPedges{make_tuple(1,0,1), make_tuple(4,0,2), make_tuple(2,1,2), make_tuple(6,1,3),make_tuple(3,2,3) };
	cout << "Read " << size << " nodes, and " << MDSPedges.size() << " edges" << endl;
	res = MyDijkstrasShortestPaths(size, MDSPedges);
	cout << "Dijkstras shortest path length from first to last node: " << res << endl;
	res = MyBellmanFordShortestPaths(size, MDSPedges);
	cout << "Bellman Ford shortest path length from first to last node: " << res << endl;

	cout << endl << "----------- MyMedianMaintenance test -----------" << endl;
	vector<int> MMMdata{10546,48328,1237,78953215,45675,123476};
	cout << "Accumulated median modulo 10000 is: " << MyMedianMaintenance(MMMdata) << endl;


	cout << endl << "----------- My2SUM test -----------" << endl;
	vector<long long> data2sum{ 1,2,3,4,5,6 };
	cout << "Count of distinct pairs of numbers summing to a value in the range [-10000,10000] is: " << My2SUM(data2sum) << endl;


	cout << endl << "----------- MyTaskScheduler test -----------" << endl;
	vector< pair<int, int> > dataTS{make_pair(2,4),make_pair(1,5),make_pair(10,2),make_pair(5,11),make_pair(4,6) };
	pair<long long, long long> MTSout = MyTaskScheduler(dataTS);
	cout << "Weighted sum of completion times under (weight-length) ordering: " << MTSout.first << endl;
	cout << "Weighted sum of completion times under (weight/length) ordering: " << MTSout.second << endl;

	cout << endl << "----------- MyPrimsMinimumSpanningTree test -----------" << endl;
	vector< tuple<int, int, int> > MPMSTdataEdges{make_tuple(6,0,1),make_tuple(3,0,2), make_tuple(4,0,3), make_tuple(2,1,2), make_tuple(5,2,3)};
	size = 4;
	long long MPMSTout = MyPrimsMinimumSpanningTree(size, MPMSTdataEdges);
	cout << "The total cost of a minimum spanning tree is: " << MPMSTout << endl;


	cout << endl << "----------- MyMaxSpacingCluster test -----------" << endl;
	vector< tuple<int, int, int> > data{ make_tuple(1, 0, 1),make_tuple(1, 2, 3),make_tuple(2, 0, 2),make_tuple(3, 1, 3),make_tuple(5, 0, 4),make_tuple(6, 2, 5) };
	size = 6;
	int MMSCout = MyMaxSpacingCluster(2, size, data);
	cout << "Smallest spacing once 2 clusters remain: " << MMSCout << endl;

	cout << endl << "----------- MyHuffmanCode test -----------" << endl;
	vector< int > MHCdata{10,9,45,7,4,8};
	pair<int, int> MHCout = MyHuffmanCode(MHCdata);
	cout << "Length of longest encoding in the Huffman code: " << MHCout.second << endl;
	cout << "Length of shortest encoding in the Huffman code: " << MHCout.first << endl;

	cout << endl << "----------- MyMaxIndependentSet test -----------" << endl;
	vector< int > MMISdata{3,1,5,7,4,9};
	string MMISout = MyMaxIndependentSet(MMISdata);
	cout << "Which of vertices 0, 1, 2, 3, 4, 5 are present in the independent set: " << MMISout << endl;


	cout << endl << "----------- MyKnapsack test -----------" << endl;
	vector< pair<unsigned long long, unsigned long long> > MKdata{ make_pair(3,5) ,make_pair(2,1) , make_pair(7,10) , make_pair(4,2) , make_pair(3,8)  };
	unsigned long long capacity = 15;
	unsigned long long MKout = MyKnapsack(MKdata, capacity);
	cout << "Maximum value of items that can be stored in the knapsack: " << MKout << endl;


	cout << endl << "----------- MyJohnsonsAllPairShortestPaths test -----------" << endl;
	vector<tuple<weight_type, int, int>> MJAPSPedges{ make_tuple(-1,0,1), make_tuple(4,0,2), make_tuple(-2,1,2), make_tuple(6,1,3),make_tuple(-3,2,3),make_tuple(7,3,0) };
	size = 4;
	int MJAPSPout = MyJohnsonsAllPairShortestPaths(size, MJAPSPedges);
	cout << "Smallest length shortest path in the graph is: " << MJAPSPout << endl;


	cout << endl << "----------- MyTravelingSalesman test -----------" << endl;
	size = 5;
	vector< pair<long double, long double> > MTSdata{make_pair(20833.3333,7100.0000),make_pair(20900.0000,17066.6667), make_pair(21300.0000,13016.6667), make_pair(21600.0000,14150.0000), make_pair(21600.0000,14966.6667), };
	vector<vector<double>> distances(size, vector<double>(size, 0.));
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			distances[i][j] = (double)sqrt(pow(MTSdata[i].first - MTSdata[j].first, 2) + pow(MTSdata[i].second - MTSdata[j].second, 2));
			distances[j][i] = distances[i][j];
		}
	}
	unsigned long long MTrSout = MyTravelingSalesman(distances);
	cout << "Smallest cost round trip: " << MTrSout << endl;


	cout << endl << "----------- MyTravelingSalesmanNearestNeighbors test -----------" << endl;
	unsigned long long MtrSNNout = MyTravelingSalesmanNearestNeighbors(MTSdata);
	cout << "Smallest cost round trip: " << MtrSNNout << endl;


	cout << endl << "----------- My2SAT test -----------" << endl;
	vector< pair<int, int> > M2Sinput{make_pair(1,-2),make_pair(-1,6),make_pair(-1,-3),make_pair(2,4),make_pair(4,-5),make_pair(5,6) };
	vector< pair<int, int> > M2Sdata;
	n = 6;
	int  x, y, cnt=0;
	while (cnt < n) {
		x = M2Sinput[cnt].first;
		y = M2Sinput[cnt].second;
		if (x < 0 && y < 0) {
			M2Sdata.push_back(make_pair(-x - 1, n - y - 1));
			M2Sdata.push_back(make_pair(-y - 1, n - x - 1));
		}
		else if (x < 0 && y>0) {
			M2Sdata.push_back(make_pair(-x - 1, y - 1));
			M2Sdata.push_back(make_pair(n + y - 1, n - x - 1));
		}
		else if (x > 0 && y < 0) {
			M2Sdata.push_back(make_pair(n + x - 1, n - y - 1));
			M2Sdata.push_back(make_pair(-y - 1, x - 1));
		}
		else if (x > 0 && y > 0) {
			M2Sdata.push_back(make_pair(n + x - 1, y - 1));
			M2Sdata.push_back(make_pair(n + y - 1, x - 1));
		}
		cnt++;
	}
	int M2Sout = My2SAT(2 * n, M2Sdata);
	if (M2Sout) {
		cout << "The 2SAT instance is satisfiable." << endl;
	}
	else {
		cout << "The 2SAT instance is NOT satisfiable." << endl;
	}
}

