
//номер посылки - 151014006

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::pair;

int constructNewTree(int v, const vector<vector<int>>& children, vector<int>& newTree, vector<int>& newTreeIndexes, vector<pair<int, int>>& subtreeCoord) {
	newTree.push_back(v);
	newTreeIndexes[v] = newTree.size() - 1;
	subtreeCoord[v].first = newTree.size() - 1;
	int lastCoord = newTree.size();
	for (int i = 0; i < children[v].size(); ++i) {
		lastCoord = constructNewTree(children[v][i], children, newTree, newTreeIndexes, subtreeCoord);
	}
	subtreeCoord[v].second = lastCoord;
	return lastCoord;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, parent;
	cin >> n;
	vector<vector<int>> children(n);
	int root;
	for (int i = 0; i < n; ++i) {
		cin >> parent;
		if (parent == 0) root = i;
		else children[parent - 1].push_back(i);
	}
	vector<pair<int, int>> subtreeCoord(n);
	vector<int> newTree;
	vector<int> newTreeIndexes(n);
	constructNewTree(root, children, newTree, newTreeIndexes, subtreeCoord);
	int m, a, b;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		if (newTreeIndexes[b - 1] < subtreeCoord[a - 1].second && newTreeIndexes[b - 1] >= subtreeCoord[a - 1].first) {
			cout << 1 << std::endl;
		}
		else {
			cout << 0 << std::endl;
		}
	}
}
