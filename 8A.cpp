
//посылка - 153483253

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;
using std::string;
using std::queue;

static const int fieldSize = 8;
static const int cells = fieldSize * fieldSize;

int indByCoord(int x, int y) {
	return y * fieldSize + x;
}

bool onBoard(int x, int y) {
	if (x >= 0 && x < fieldSize && y >= 0 && y < fieldSize) return true;
	return false;
}

pair<int, int> coordByInd(int ind) {
	return {ind % 8, ind / 8};
}

pair<char, int> stringCoordByInd(int ind) {
	pair coord = coordByInd(ind);
	return {'a' + coord.first, coord.second + 1};
}

void getEdges(vector<vector<int>>& g, int ind) {
	pair coord = coordByInd(ind);
	int x = coord.first, y = coord.second;
	for (int sign1 = -1; sign1 < 2; sign1 += 2) {
		for (int value1 = 1; value1 < 3; ++value1) {
			for (int sign2 = -1; sign2 < 2; sign2 += 2) {
				int value2 = 3 - value1;
				int tmpx = x + sign1 * value1;
				int tmpy = y + sign2 * value2;
				if (onBoard(tmpx, tmpy)) {
					g[ind].push_back(indByCoord(tmpx, tmpy));
				}
			}
		}
	}
}

void buildGraph(vector<vector<int>>& g) {
	for (int i = 0; i < cells; ++i) {
		getEdges(g, i);
	}
}

void bfs(const vector<vector<int>>& g, vector<int>& dist, vector<vector<int>>& route, int s) {
	queue<int> vert;
	vert.push(s);
	dist[s] = 0;
	route[s].push_back(s);
	while (!vert.empty()) {
		int v = vert.front();
		vert.pop();
		for (int e : g[v]) {
			if (dist[e] == INT_MAX) {
				dist[e] = dist[v] + 1;
				route[e] = route[v];
				route[e].push_back(e);
				vert.push(e);
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	string first, second;
	std::cin >> first >> second;
	vector<vector<int>> g(cells);
	buildGraph(g);
	vector<int> dist(cells, INT_MAX);
	vector<vector<int>> route(cells);
	int x1 = first[0] - 'a';
	int y1 = first[1] - '1';
	int start = indByCoord(x1, y1);
	bfs(g, dist, route, start);
	int x2 = second[0] - 'a';
	int y2 = second[1] - '1';
	int finish = indByCoord(x2, y2);
	for (int i = 0; i < route[finish].size(); ++i) {
		pair strCoord = stringCoordByInd(route[finish][i]);
		std::cout << strCoord.first << strCoord.second << std::endl;
	}
}
