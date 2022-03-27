
//номер посылки - 151075617

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

void eulerCycle(int v, const vector<vector<int>>& reversedGraph, vector<int>& notBuilt, vector<int>& ans) {
	while (notBuilt[v] != 0) {
		--notBuilt[v];
		eulerCycle(reversedGraph[v][notBuilt[v]], reversedGraph, notBuilt, ans);
	}
	ans.push_back(v);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, a;
	bool channel;
	cin >> n >> a;
	vector<vector<int>> reversedAntiGraph(n);
	vector<int> notBuilt(n, 0);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> channel;
			if (!channel && i != j) {
				reversedAntiGraph[j].push_back(i);
				notBuilt[j] += 1;
			}
		}
	}
	vector<int> ans;
	eulerCycle(a - 1, reversedAntiGraph, notBuilt, ans);
	for (int i = 0; i < ans.size() - 1; ++i) {
		cout << ans[i] + 1 << " " << ans[i + 1] + 1 << std::endl;
	}
}
