#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct Node {

public:

	long long leftNode = -1;
	long long rightNode = -1;
	long long leftCoordinate = -1;
	long long rightCoordinate = -1;
	long long value = 0;

	Node(long long lN, long long rN, long long leftC, long long rightC, long long v):leftNode(lN), rightNode(rN),
	leftCoordinate(leftC), rightCoordinate(rightC), value(v) {}
	
	void operator= (Node &n) {
		leftNode = n.leftNode;
		rightNode = n.rightNode;
		leftCoordinate = n.leftCoordinate;
		rightCoordinate = n.rightCoordinate;
		value = n.value;
	}
};

class SegmentTree {
private:

	vector <Node> Tree = { Node(-1, -1, 0, 1073741824, 0) };

public:

	SegmentTree(): Tree(1, Node(-1, -1, 0, 1073741824, 0)) {}

void Insert(long long value) { 
	Tree[0].value += value;
	long long ind = 0;
	while (Tree[ind].leftCoordinate != Tree[ind].rightCoordinate) {
		if (Tree[ind].leftNode == -1) {
			Tree[ind].leftNode = Tree.size();
			Tree.push_back(Node(-1, -1, Tree[ind].leftCoordinate, (Tree[ind].leftCoordinate + Tree[ind].rightCoordinate) / 2 , 0));
		}
		if (Tree[ind].rightNode == -1) {
			Tree[ind].rightNode = Tree.size();
			Tree.push_back(Node(-1, -1, (Tree[ind].leftCoordinate + Tree[ind].rightCoordinate) / 2 + 1, Tree[ind].rightCoordinate, 0));
		}
		if (Tree[Tree[ind].rightNode].leftCoordinate <= value && value <= Tree[Tree[ind].rightNode].rightCoordinate) {
			ind = Tree[ind].rightNode;
		}
		else if (Tree[Tree[ind].leftNode].leftCoordinate <= value && value <= Tree[Tree[ind].leftNode].rightCoordinate) {
			ind = Tree[ind].leftNode;
		}
		Tree[ind].value += value;
	}
}

long long GetSum(long long x) const {
	return getSum(0, x);
}

long long getSum(long long index, long long right) const {
	if (index == -1) { return 0; }
	if (right < Tree[index].leftCoordinate) { return 0; }

	if (Tree[index].rightCoordinate <= right) {
		return Tree[index].value;
	}

	long long l = getSum(Tree[index].leftNode, right);
	long long r = getSum(Tree[index].rightNode, right);

	return l + r;
}

};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int q;
	char input;
	long long x;
	cin >> q;
	SegmentTree Tree = SegmentTree();
	vector <long long> answer;
	for (int i = 0; i < q; ++i) {
		cin >> input >> x;
		if (input == '+') {
			Tree.Insert(x);
		}
		else {
			answer.push_back(Tree.GetSum(x));
		}
	}
	for (auto& i : answer) {
		cout << i << endl;
	}
}
