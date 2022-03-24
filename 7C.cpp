
//послыка - 150806181

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

void getMyCycle(int start, int end, vector<int>& parent) {
	cout << "YES" << std::endl;
	vector<int> ans;
	int v = start;
	while (v != end) {
		ans.push_back(v);
		v = parent[v];
	}
	ans.push_back(v);
	for (int i = ans.size() - 1; i >= 0; --i) {
		cout << ans[i] + 1 << " ";
	}
}

bool dfs(int v, vector<vector<int>>& graph, vector<int>& parent, vector<int>& color) {
	color[v] = 1;
	bool cycleFound = false;
	for (int i = 0; i < graph[v].size(); ++i) {
		int nextv = graph[v][i];
		if (color[nextv] == 1) {
			cycleFound = true;
			getMyCycle(v, nextv, parent);
		}
		else if (color[nextv] == 0) {
			parent[nextv] = v;
			cycleFound = dfs(nextv, graph, parent, color);
		}
		if (cycleFound) break;
	}
	color[v] = 2;
	return cycleFound;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, u, v;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
	}
	vector<int> color(n, 0);
	vector<int> parent(n, -1);
	bool cycleFound = false;
	for (int i = 0; i < n; ++i) {
		if (color[i] == 0) cycleFound = dfs(i, graph, parent, color);
		if (cycleFound) break;
	}
	if(!cycleFound) cout << "NO" << std::endl;
}
