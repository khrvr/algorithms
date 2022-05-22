
//посылка - 155853225

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
using std::cin;
using std::cout;
using std::swap;

pair<char, char> getZero(unsigned long long st) {
	for (int i = 0; i < 16; ++i) {
		if (((st << ((15 - i) * 4)) >> 60) == 0) return { i / 4, i % 4 };
	}
}

bool solutionExists(unsigned long long s) {
	vector<char> elem;
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			char curr = ((s << ((15 - (i * 4 + j)) * 4)) >> 60);
			if (curr == 0) ans += i;
			else {
				for (int q = 0; q < elem.size(); ++q) {
					if (elem[q] > curr) ++ans;
				}
				elem.push_back(curr);
			}
		}
	}
	return (ans % 2);
}

//моя реализация кучи

int heu(unsigned long long s, const vector<char>& correctCells) {
	int ans = 0;
	vector<vector<char>> cells(4, vector<char>(4));
	for (char i = 0; i < 4; ++i) {
		for (char j = 0; j < 4; ++j) {
			char tmp = ((s << ((15 - (i * 4 + j)) * 4)) >> 60);
			cells[i][j] = tmp;
			if (tmp == 0) continue;
			char rtRow = correctCells[tmp] / 4;
			char rtColumn = correctCells[tmp] % 4;
			if (rtRow == i) {
				for (char x = 0; x < j; ++x) {
					if (cells[i][x] != 0 && rtColumn < (correctCells[cells[i][x]] % 4)) ans += 2;
				}
			}
			if (rtColumn == j) {
				for (char x = 0; x < i; ++x) {
					if (cells[x][j] != 0 && rtRow < (correctCells[cells[x][j]] / 4)) ans += 2;
				}
			}
			ans += abs(i - rtRow) + abs(j - rtColumn);
		}
	}
	return ans;
}


unsigned long long bitswap(unsigned long long st, char a, char b) {
	unsigned long long first = ((st << ((15 - a) * 4)) >> 60);
	unsigned long long second = ((st << ((15 - b) * 4)) >> 60);
	st -= (first << (4 * a)) + (second << (4 * b));
	return st += (first << (4 * b)) + (second << (4 * a));
}

unsigned long long moveZero(unsigned long long st, const pair<char, char>& zeroYX, int dir) {
	switch (dir) {
	case 0:
		if (zeroYX.second != 0) {
			return bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second - 1);
		}
		break;
	case 1:
		if (zeroYX.second != 3) {
			return bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second + 1);
		}
		break;
	case 2:
		if (zeroYX.first != 0) {
			return bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second - 4);
		}
		break;
	case 3:
		if (zeroYX.first != 3) {
			return bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second + 4);
		}
		break;
	case 4:
		if (zeroYX.second >= 2) {
			st = bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second - 1);
			return bitswap(st, zeroYX.first * 4 + zeroYX.second - 1, zeroYX.first * 4 + zeroYX.second - 2);
		}
		break;
	case 5:
		if (zeroYX.second <= 1) {
			st = bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second + 1);
			return bitswap(st, zeroYX.first * 4 + zeroYX.second + 1, zeroYX.first * 4 + zeroYX.second + 2);
		}
		break;
	case 6:
		if (zeroYX.first >= 2) {
			st = bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second - 4);
			return bitswap(st, zeroYX.first * 4 + zeroYX.second - 4, zeroYX.first * 4 + zeroYX.second - 8);
		}
		break;
	case 7:
		if (zeroYX.first <= 1) {
			st = bitswap(st, zeroYX.first * 4 + zeroYX.second, zeroYX.first * 4 + zeroYX.second + 4);
			return bitswap(st, zeroYX.first * 4 + zeroYX.second + 4, zeroYX.first * 4 + zeroYX.second + 8);
		}
		break;
	}
	return 0;
}

void getNeigh(unsigned long long st, vector<unsigned long long>& ans) {
	pair<char, char> zeroYX = getZero(st);
	for (int i = 0; i < 8; ++i) {
		ans.push_back(moveZero(st, zeroYX, i));
	}
}


unsigned long long oneAstar(unsigned long long s, unsigned long long f, const vector<char>& cellsf, unordered_map<unsigned long long, pair<unsigned long long, char>>& parents, unordered_map<unsigned long long, char>& dists, unordered_map<unsigned long long, char>& distf, binHeap& distHeaps, unordered_map<unsigned long long, int>& heapInserts) {
	unsigned long long v = distHeaps.getMinKey();
	if (distf.contains(v))
		return v;
	distHeaps.extractMin();
	heapInserts.erase(v);
	vector<unsigned long long> neigh;
	getNeigh(v, neigh);
	for (int x = 0; x < neigh.size(); ++x) {
		unsigned long long to = neigh[x];
		if (to == 0) continue;
		if (!dists.contains(to) || dists[to] > dists[v] + 1) {
			dists[to] = dists[v] + 1;
			parents[to] = { v, x };
			int total = dists[to] + heu(to, cellsf);
			if (!heapInserts.contains(to)) heapInserts[to] = distHeaps.insert(total, to);
			else distHeaps.changeKey(heapInserts[to], total);
		}
	}
	return 0;
}

unsigned long long parallelAstar(unsigned long long s, unsigned long long f, vector<char>& cellss, vector<char>& cellsf, unordered_map<unsigned long long, pair<unsigned long long, char>>& parents, unordered_map<unsigned long long, pair<unsigned long long, char>>& parentf) {
	binHeap distHeaps, distHeapf;
	unordered_map<unsigned long long, char> dists, distf;
	unordered_map<unsigned long long, int> heapInserts, heapInsertf;
	dists[s] = 0;
	heapInserts[s] = distHeaps.insert(heu(s, cellsf), s);
	parents[s] = { 0, 100 };
	distf[f] = 0;
	heapInsertf[f] = distHeapf.insert(heu(f, cellss), f);
	parentf[f] = { 0, 100 };
	while (true) {
		unsigned long long anss = oneAstar(s, f, cellsf, parents, dists, distf, distHeaps, heapInserts);
		if (anss) return anss;
		unsigned long long ansf = oneAstar(f, s, cellss, parentf, distf, dists, distHeapf, heapInsertf);
		if (ansf) return ansf;
	}
}

void getRoute(string& route, int& actualans, char direction, bool reverse) {
	switch (direction) {
	case 0:
		route.push_back(reverse ? 'L' : 'R');
		actualans += 1;
		break;
	case 1:
		route.push_back(reverse ? 'R' : 'L');
		actualans += 1;
		break;
	case 2:
		route.push_back(reverse ? 'U' : 'D');
		actualans += 1;
		break;
	case 3:
		route.push_back(reverse ? 'D' : 'U');
		actualans += 1;
		break;
	case 4:
		route.append(reverse ? "LL" : "RR");
		actualans += 2;
		break;
	case 5:
		route.append(reverse ? "RR" : "LL");
		actualans += 2;
		break;
	case 6:
		route.append(reverse ? "UU" : "DD");
		actualans += 2;
		break;
	case 7:
		route.append(reverse ? "DD" : "UU");
		actualans += 2;
		break;
	}
}

signed main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	unsigned long long s = 0;
	unsigned long long f = 1147797409030816545;
	vector<char> cellsf = { 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	vector<char> cellss(16);
	unsigned long long inp;
	for (char i = 0; i < 4; ++i) {
		for (char j = 0; j < 4; ++j) {
			cin >> inp;
			s += (inp << ((i * 4 + j) * 4));
			cellss[inp] = i * 4 + j;
		}
	}
	if (!solutionExists(s)) {
		cout << -1 << std::endl;
		return 0;
	}
	unordered_map<unsigned long long, pair<unsigned long long, char>> parents;
	unordered_map<unsigned long long, pair<unsigned long long, char>> parentf;
	unsigned long long v = parallelAstar(s, f, cellss, cellsf, parents, parentf);
	int actualans = 0;
	auto parentFromS = parents[v];
	string route = "";
	while (parentFromS.second != 100) {
		getRoute(route, actualans, parentFromS.second, false);
		parentFromS = parents[parentFromS.first];
	}
	std::reverse(route.begin(), route.end());
	auto parentFromF = parentf[v];
	while (parentFromF.second != 100) {
		getRoute(route, actualans, parentFromF.second, true);
		parentFromF = parentf[parentFromF.first];
	}
	cout << actualans << std::endl;
	if (route != "") cout << route;
}
