
//посылка - 156142545

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cin;
using std::cout;

struct edge {
    int v1;
    int v2;
    int weight;
};

class dsu {

    vector<int> parents;
    vector<int> size;

public:

    dsu() = delete;

    dsu(int n) : parents(n, -1), size(n, 1) {}

    int get(int v) {
        if (parents[v] == -1)
            return v;
        return parents[v] = get(parents[v]);
    }

    void unite(int u, int v) {
        v = get(v);
        u = get(u);
        if (v == u)
            return;
        if (size[u] > size[v])
            std::swap(u, v);
        parents[u] = v;
        size[v] += size[u];
    }

};

int kruskal(const vector<vector<int>>& graph, const vector<edge>& edges) {
    int sum = 0;
    vector<pair<int, int>> sortedEdges(edges.size());
    for (int i = 0; i < edges.size(); ++i)
        sortedEdges[i] = {edges[i].weight, i};
    std::sort(sortedEdges.begin(), sortedEdges.end());
    dsu vertices(graph.size());
    for (int i = 0; i < sortedEdges.size(); ++i) {
        int v1 = edges[sortedEdges[i].second].v1;
        int v2 = edges[sortedEdges[i].second].v2;
        if (vertices.get(v1) != vertices.get(v2)) {
            vertices.unite(v1, v2);
            sum += edges[sortedEdges[i].second].weight;
        }
    }
    return sum;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<edge> edges;
    vector<vector<int>> graph(n);
    int b, e, w;
    for (int i = 0; i < m; ++i) {
        cin >> b >> e >> w;
        edges.push_back({b - 1, e - 1, w});
        graph[b - 1].push_back(i);
        graph[e - 1].push_back(i);
    }
    cout << kruskal(graph, edges);
}
