// Code by Michael Zlotnikov 05/2021

#include "MyHuffmanCode.h"

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
	int parent,weight,depth;
	int child[2];
};

class MyHuffman {
public:
	int n;
	vector<struct node> nodes;
	vector<string> codes;
	priority_queue<pair<int,int>,vector<pair<int, int>>, greater<pair<int, int>> > q;

	MyHuffman(vector<int> & vec) {
		n = vec.size();
		nodes.resize(n);
		codes.resize(n);
		for (int i = 0; i < n; i++) {
			codes[i] = "";
			nodes[i].depth = 1;
			nodes[i].weight = vec[i];
			nodes[i].parent = -1;
			nodes[i].child[0] = -1;
			nodes[i].child[1] = -1;
			q.push(make_pair(vec[i], i));
		}
		constructTree();
		constructCodes();
	}
	void constructTree() {
		while (q.size() > 0) {
			pair<int, int> one, two;
			one = q.top();
			q.pop();
			two = q.top();
			q.pop();
			struct node nd;
			nd.depth = max(nodes[one.second].depth, nodes[two.second].depth) + 1;
			nd.weight = one.first + two.first;
			nd.parent = -1;
			nd.child[0] = one.second;
			nd.child[1] = two.second;
			nodes.push_back(nd);
			nodes[one.second].parent = nodes.size() - 1;
			nodes[two.second].parent = nodes.size() - 1;
			if (q.size() > 0) {
				q.push(make_pair(nd.weight, nodes.size() - 1));
			}
		}
	}
	void constructCodes() {
		for (int i = 0; i < n; i++) {
			int pos = i,next;
			while (pos < nodes.size() - 1) {
				next = nodes[pos].parent;
				if (nodes[next].child[0] == pos) {
					codes[i] = "0" + codes[i];
				} else {
					codes[i] = "1" + codes[i];
				}
				pos = next;
			}
		}
	}
	vector<int> decodeMessage(string s) {
		vector<int> message;
		int pos = nodes.size() - 1;
		for (int i = 0; i < s.size(); i++) {
			if(nodes[pos].child[0] == -1) {
				message.push_back(pos);
				pos = nodes.size() - 1;
			}
			if (s[i] == '0') {
				pos = nodes[pos].child[0];
			} else {
				pos = nodes[pos].child[1];
			}
		}
		return message;
	}
	string encodeMessage(vector<int> message) {
		string encoding = "";
		for (int i = 0; i < message.size(); i++) {
			encoding += codes[message[i]];
		}
		return encoding;
	}
};

pair<int,int> MyHuffmanCode(vector<int> & vec) {
	MyHuffman huff(vec);
	int maxLen= 0;
	int minLen = INT_MAX;
	for (int i = 0; i < vec.size(); i++) {
		if (huff.codes[i].size() < minLen) {
			minLen = huff.codes[i].size();
		}
		if (huff.codes[i].size() > maxLen) {
			maxLen = huff.codes[i].size();
		}
	}
	return make_pair(minLen, maxLen);
}
