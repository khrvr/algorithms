
//посылка - 156129044

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::pair;
using std::swap;
using std::cin;
using std::cout;

//реализация кучи

struct edge {
    int v1;
    int v2;
    int weight;
};

int prim(const vector<vector<int>>& graph, const vector<edge>& edges) {
    int sum = 0;
    vector<bool> taken(graph.size(), false);
    binHeap<int, int> cheapestEdges;
    for (int edge : graph[0])
        cheapestEdges.insert(edge, edges[edge].weight);
    taken[0] = true;
    for (int i = 0; i < graph.size() - 1; ++i) {
        int cheapestEdge = cheapestEdges.getMinKey();
        int v1 = edges[cheapestEdge].v1;
        int v2 = edges[cheapestEdge].v2;
        sum += edges[cheapestEdge].weight;
        int newlyTaken = v1 * (1 - taken[v1]) + v2 * (1 - taken[v2]);
        taken[newlyTaken] = true;
        for (int edge : graph[newlyTaken]) {
            int v = edges[edge].v1 + edges[edge].v2 - newlyTaken;
            if (taken[v])
                cheapestEdges.erase(edge);
            else
                cheapestEdges.insert(edge, edges[edge].weight);
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
    cout << prim(graph, edges);
}
