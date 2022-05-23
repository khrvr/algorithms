
//посылка - 156366270

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

bool augment(int v, const vector<vector<int>>& g, vector<bool>& used, vector<int>& match) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (match[to] == -1 || augment(match[to], g, used, match)) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int m, n, u, v;
    cin >> n >> m;
    vector<vector<int>> g1(n);
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        g1[u - 1].push_back(v - 1);
    }
    vector<int> match(n, -1);
    vector<bool> used(n, false);
    for (int i = 0; i < g1.size(); ++i) {
        if (augment(i, g1, used, match)) {
            std::fill(used.begin(), used.end(), false);
        }
    }
    int ans = 0;
    for (int i = 0; i < match.size(); ++i) {
        if (match[i] == -1)
            ++ans;
    }
    cout << ans;
}
