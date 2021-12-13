#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int degree2(int value) {
	int i = 0;
	while (value >> i) ++i;
	return 1 << i;
}

class SegmentTree {
public:

	SegmentTree(vector <pair <int, int>> arr, int defaultValue);

	int GetSum(int left, int right) const;

	void Insert(int index, int value);

private:
	vector<pair <int, int>> tree;
	int default_;

	void build(int index, int left, int right);
	pair <int, int> getSum(int index, int i_left, int i_right, int left, int right) const;
};

SegmentTree::SegmentTree(vector <pair <int, int>> arr, int defaultValue) : tree(degree2(arr.size()) * 2, { defaultValue, -1 }), default_(defaultValue) {
	copy(arr.begin(), arr.end(), tree.begin() + tree.size() / 2 - 1);
	build(0, 0, tree.size() / 2 - 1);
}

void SegmentTree::build(int index, int left, int right) {
	if (left == right) return;
	const int mid = (left + right) / 2;
	build(2 * index + 1, left, mid);
	build(2 * index + 2, mid + 1, right);
	pair <int, int> l = tree[2 * index + 1];
	pair <int, int> r = tree[2 * index + 2];
	tree[index] = make_pair(l.first - l.second * r.first, -l.second * r.second);
}

void SegmentTree::Insert(int index, int value) {
	int realIndex = tree.size() / 2 + index - 1;
	tree[realIndex] = { value, 1 };
	int prevIndex = (realIndex - 1) / 2;
	pair <int, int> l = tree[2 * prevIndex + 1];
	pair <int, int> r = tree[2 * prevIndex + 2];
	while (tree[prevIndex] != make_pair(l.first - l.second * r.first, -l.second * r.second)) {
		tree[prevIndex] = make_pair(l.first - l.second * r.first, -l.second * r.second);
		prevIndex = (prevIndex - 1) / 2;
		l = tree[2 * prevIndex + 1];
		r = tree[2 * prevIndex + 2];
	}
}

int SegmentTree::GetSum(int left, int right) const {
	return getSum(0, 0, tree.size() / 2 - 2, left, right).first;
}

pair <int, int> SegmentTree::getSum(int index, int i_left, int i_right, int left, int right) const {
	if (right < i_left) { return { default_ , -1 }; }
	if (i_right < left) { return { default_ , -1 }; }

	if (left <= i_left && i_right <= right) {
		return tree[index];
	}

	const int mid = (i_left + i_right) / 2;
	pair <int, int> l = getSum(2 * index + 1, i_left, mid, left, right);
	pair <int, int> r = getSum(2 * index + 2, mid + 1, i_right, left, right);
	return make_pair(l.first - l.second * r.first, -l.second * r.second);
}

int main()
{
	int n, input;
	vector <pair <int, int>> arr;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		arr.push_back({ input, 1 });
	}
	SegmentTree tree = SegmentTree(arr, 0);
	int m, x, y;
	cin >> m;
	vector <int> answer;
	for (int e = 0; e < m; ++e) {
		cin >> input >> x >> y;
		if (input == 0) {
			tree.Insert(x - 1, y);
		}
		else {
			answer.push_back(tree.GetSum(x - 1, y - 1));
		}
	}
	for (auto& i : answer) {
		cout << i << endl;
	}
}
