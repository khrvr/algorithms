
//посылка - 157365411

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::cin;
using std::cout;
using std::unordered_multiset;

void dfs(int v, int t, const vector<unordered_multiset<int>>& graph, vector<bool>& used, vector<int>& parent) {
    if (v == t)
        return;
    used[v] = 1;
    for (auto i = graph[v].begin(); i != graph[v].end(); ++i) {
        int nextv = *i;
        if (used[nextv] == 0) {
            parent[nextv] = v;
            dfs(nextv, t, graph, used, parent);
        }
    }
}

void updateGraph(int v, vector<unordered_multiset<int>>& graph, const vector<int>& parent) {
    int parentV = parent[v];
    while (parentV != -1) {
        graph[v].insert(parentV);
        graph[parentV].erase(graph[parentV].find(v));
        v = parentV;
        parentV = parent[v];
    }
}

vector<int> cleanParent(int t, const vector<int>& parent) {
    vector<int> cleanParent(parent.size(), -1);
    int v = t;
    while (parent[v] != -1) {
        cleanParent[v] = parent[v];
        v = parent[v];
    }
    return cleanParent;
}

vector<int> getRoute(int t, const vector<int>& parentFirst, const vector<int>& parentSecond) {
    vector<int> route;
    int v = t;
    route.push_back(v);
    auto parent = &parentFirst;
    auto otherParent = &parentSecond;
    while (parent->operator[](v) != -1) {
        int newV = parent->operator[](v);
        if (otherParent->operator[](newV) == v) {
            std::swap(parent, otherParent);
        }
        v = parent->operator[](v);
        route.push_back(v);
    }
    return route;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s; --t;
    vector<unordered_multiset<int>> graph(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        graph[u - 1].insert(v - 1);
    }
    vector<bool> used(n, false);
    vector<int> parentFirst(n, -1);
    dfs(s, t, graph, used, parentFirst);
    if (parentFirst[t] == -1) {
        cout << "NO";
        return 0;
    }
    updateGraph(t, graph, parentFirst);
    parentFirst = cleanParent(t, parentFirst);
    std::fill(used.begin(), used.end(), false);
    vector<int> parentSecond(n, -1);
    dfs(s, t, graph, used, parentSecond);
    if (parentSecond[t] == -1) {
        cout << "NO";
        return 0;
    }
    parentSecond = cleanParent(t, parentSecond);
    cout << "YES" << std::endl;
    vector<int> route(getRoute(t, parentFirst, parentSecond));
    for (int i = route.size() - 1; i >= 0; --i)
        cout << route[i] + 1 << " ";
    cout << std::endl;
    route = getRoute(t, parentSecond, parentFirst);
    for (int i = route.size() - 1; i >= 0; --i)
        cout << route[i] + 1 << " ";
}
