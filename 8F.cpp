
//посылка - 153489647

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using std::vector;
using std::pair;
using std::swap;

static const int inf = INT_MAX;

//класс binHeap из одного из предыдущих заданий

struct edge {
	int vertIndSum;
	int weight;
	edge() = delete;
	edge(int v, int w) : vertIndSum(v), weight(w) {}
};

void dijkstra(const vector<vector<int>>& g, const vector<edge>& edges, vector<int>& dist, binHeap& distHeap, int s) {
	distHeap.decreaseKey(s, inf);
	while (!distHeap.empty()) {
		int v = distHeap.getMinKey();
		if (dist[v] == inf) return;
		distHeap.extractMin();
		for (int eInd : g[v]) {
			edge e = edges[eInd];
			int to = e.vertIndSum - v;
			if (dist[to] > dist[v] + e.weight) {
				distHeap.decreaseKey(to, dist[to] - (dist[v] + e.weight));
				dist[to] = dist[v] + e.weight;
			}
		}
	}
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, m, s, t, b, e, w;
	std::cin >> n >> m >> s >> t;
	--s;
	--t;
	vector<vector<int>> g(n);
	vector<edge> edges;
	for (int i = 0; i < m; ++i) {
		std::cin >> b >> e >> w;
		--b; 
		--e;
		edges.push_back(edge(b + e, w));
		g[b].push_back(i);
		g[e].push_back(i);
	}
	vector<int> dist(n, inf);
	binHeap distHeap;
	for (int i = 0; i < n; ++i) {
		distHeap.insert(inf, i);
	}
	dijkstra(g, edges, dist, distHeap, s);
	if (dist[t] == inf) std::cout << "-1";
	else std::cout << dist[t];

}
