#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector <int> degree2(int n) {
	vector <int> deg;
	deg.push_back(0);
	deg.push_back(1);
	for (int i = 2; i < n; ++i) {
		deg.push_back(deg[i - 1]);
		if ((i & (i + 1)) == 0) {
			++deg[i];
		}
	}
	return deg;
}

class sparseTable {

	vector<int> deg;
	vector <vector <pair <int, int>>> sparse;
	const int n;

public:

	sparseTable(int n): deg(degree2(n)), sparse(deg[n - 1] + 1), n(n) {}

	void insert1(int a, int b) {
		sparse[1].push_back(make_pair(a, b));
	}

	void prepare(vector<int>& sequence) {
		for (int i = 2; i < sparse.size(); ++i) {
			for (int j = 0; j < n; ++j) {
				pair <int, int> f = sparse[i - 1][j];
				pair <int, int> s;
				if ((j + (1 << (i - 1))) <= n - 1) {
					s = sparse[i - 1][j + (1 << (i - 1))];
				}
				else {
					sparse[i].push_back(f);
					continue;
				}
				if (sequence[f.first] < sequence[s.first]) {
					if (f.second != n && sequence[f.second] < sequence[s.first]) {
						sparse[i].push_back(make_pair(f.first, f.second));
					}
					else {
						sparse[i].push_back(make_pair(f.first, s.first));
					}
				}
				else {
					if (s.second != n && sequence[s.second] < sequence[f.first]) {
						sparse[i].push_back(make_pair(s.first, s.second));
					}
					else {
						sparse[i].push_back(make_pair(s.first, f.first));
					}
				}
			}
		}
	}

	int get(vector <int>& sequence, int l, int r) const {
		pair <int, int> f = sparse[deg[r - l]][l];
		pair <int, int> s = sparse[deg[r - l]][r + 1 - (1 << deg[r - l])];
		if (sequence[f.first] < sequence[s.first]) {
			if (f.second != n && sequence[f.second] < sequence[s.first]) {
				return (sequence[f.second]);

			}
			else {
				return (sequence[s.first]);
			}
		}
		else if (sequence[f.first] > sequence[s.first]) {
			if (s.second != n && sequence[s.second] < sequence[f.first]) {
				return (sequence[s.second]);
			}
			else {
				return (sequence[f.first]);
			}
		}
		else {
			if (f.first != s.first) {
				return (sequence[f.first]);
			}
			else {
				if (s.second != n && sequence[s.second] < sequence[f.second]) {
					return (sequence[s.second]);
				}
				else {
					return (sequence[f.second]);
				}
			}
		}
	}

};

int main() {

	int n, m;
	cin >> n >> m;
	sparseTable st = sparseTable(n);
	vector <int> sequence;
	int input, prev;
	cin >> input;
	sequence.push_back(input);
	prev = input;
	for (int i = 1; i < n; ++i) {
		cin >> input;
		sequence.push_back(input);
		if (input < prev) {
			st.insert1(i, i - 1);
		}
		else {
			st.insert1(i - 1, i);
		}
		prev = input;
	}
	st.insert1(n - 1, n);
	st.prepare(sequence);
	int l, r;
	vector <int> answer;
	for (int i = 0; i < m; ++i) {
		cin >> l >> r;
		--l, --r;
		answer.push_back(st.get(sequence, l, r));
	}
	for (auto& i : answer) {
		cout << i << '\n';
	}
}
