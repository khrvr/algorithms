
//номер посылки - 138003280

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

struct Node {
	int value = -1;
	int depth = 1;
	int prev = -1;
	int leftNode = -1;
	int rightNode = -1;
	Node(int x, int previous): value(x), prev(previous){}
	Node() = default;
	void operator=(const Node& other) {
		value = other.value;
		depth = other.depth;
		prev = other.prev;
		leftNode = other.leftNode;
		rightNode = other.rightNode;
	}
};

class AVL {
	vector <Node> avl;
	stack <int> emptyNodes;

	void avlSwap(int index1, int index2) {
		std::swap(avl[index1].value, avl[index2].value);
	}

	int newNode(int x, int prev) {
		if (emptyNodes.empty()) {
			avl.push_back(Node(x, prev));
			return avl.size() - 1;
		}
		else {
			int index = emptyNodes.top();
			emptyNodes.pop();
			avl[index] = Node(x, prev);
			return index;
		}
	}

	int delta(int index) {
		int prn = avl[index].rightNode;
		int pln = avl[index].leftNode;
		return (pln != -1 ? avl[pln].depth : 0) - (prn != -1 ? avl[prn].depth : 0);
	}

	void fix_depth(int index) {
		if (index == -1) {
			return;
		}
		int prn = avl[index].rightNode;
		int pln = avl[index].leftNode;
		avl[index].depth = max((prn != -1 ? avl[prn].depth : 0), (pln != -1 ? avl[pln].depth : 0)) + 1;
		int tmpDepth = avl[index].depth;
		int deltaIndex = delta(index);
		if (deltaIndex == -2) {
			if (delta(prn) == 1) {
				avl[index].leftNode = avl[prn].leftNode;
				avl[avl[prn].leftNode].prev = index;
				avl[prn].leftNode = pln;
				if (pln != -1) avl[pln].prev = prn;
				avlSwap(index, avl[index].leftNode);
				swap(avl[avl[index].leftNode].leftNode, avl[avl[index].leftNode].rightNode);
				swap(avl[avl[index].rightNode].leftNode, avl[avl[index].leftNode].leftNode);
				if (avl[avl[index].leftNode].leftNode != -1) avl[avl[avl[index].leftNode].leftNode].prev = avl[index].leftNode;
				if (avl[avl[index].rightNode].leftNode != -1) avl[avl[avl[index].rightNode].leftNode].prev = avl[index].rightNode;
				avl[avl[index].leftNode].depth = tmpDepth - 2;
				avl[avl[index].rightNode].depth = tmpDepth - 2;
				avl[index].depth = tmpDepth - 1;
				fix_depth(avl[index].prev);
			}
			else {
				avlSwap(index, prn);
				swap(avl[prn].leftNode, avl[prn].rightNode);
				swap(avl[index].leftNode, avl[index].rightNode);
				swap(avl[avl[index].leftNode].leftNode, avl[index].rightNode);
				if (avl[index].rightNode != -1) avl[avl[index].rightNode].prev = index;
				if (avl[avl[index].leftNode].leftNode != -1) avl[avl[avl[index].leftNode].leftNode].prev = avl[index].leftNode;
				fix_depth(avl[index].leftNode);
			}
		}
		else if (deltaIndex == 2) {
			if (delta(pln) == -1) {
				avl[index].rightNode = avl[pln].rightNode;
				avl[avl[pln].rightNode].prev = index;
				avl[pln].rightNode = prn;
				if (prn != -1) avl[prn].prev = pln;
				avlSwap(index, avl[index].rightNode);
				swap(avl[avl[index].rightNode].rightNode, avl[avl[index].rightNode].leftNode);
				swap(avl[avl[index].leftNode].rightNode, avl[avl[index].rightNode].rightNode);
				if (avl[avl[index].rightNode].rightNode != -1) avl[avl[avl[index].rightNode].rightNode].prev = avl[index].rightNode;
				if (avl[avl[index].leftNode].rightNode != -1) avl[avl[avl[index].leftNode].rightNode].prev = avl[index].leftNode;
				avl[avl[index].rightNode].depth = tmpDepth - 2;
				avl[avl[index].leftNode].depth = tmpDepth - 2;
				avl[index].depth = tmpDepth - 1;
				fix_depth(avl[index].prev);
			}
			else {
				avlSwap(index, pln);
				swap(avl[pln].rightNode, avl[pln].leftNode);
				swap(avl[index].rightNode, avl[index].leftNode);
				swap(avl[avl[index].rightNode].rightNode, avl[index].leftNode);
				if (avl[index].leftNode != -1) avl[avl[index].leftNode].prev = index;
				if (avl[avl[index].rightNode].rightNode != -1) avl[avl[avl[index].rightNode].rightNode].prev = avl[index].rightNode;
				fix_depth(avl[index].rightNode);
			}
		}
		else {
			fix_depth(avl[index].prev);
		}
	}

	int rec_find(int x, int index) {
		if (index == -1) {
			return -1;
		}
		if (avl[index].value < x) {
			return rec_find(x, avl[index].rightNode);
		}
		else if (avl[index].value > x) {
			return rec_find(x, avl[index].leftNode);
		}
		return index;
	}

	int rec_next(int x, int index) {
		if (index == -1) {
			return INT_MAX;
		}
		if (avl[index].value <= x) {
			return rec_next(x, avl[index].rightNode);
		}	
		return min(avl[index].value, rec_next(x, avl[index].leftNode));
	}

	int rec_prev(int x, int index) {
		if (index == -1) {
			return INT_MIN;
		}
		if (avl[index].value >= x) {
			return rec_prev(x, avl[index].leftNode);
		}
		return max(avl[index].value, rec_prev(x, avl[index].rightNode));
	}

	void rec_insert(int x, int index) {
		if (avl.empty()) {
			avl.push_back(Node(x, -1));
			return;
		}
		if (avl[index].value < x) {
			if (avl[index].rightNode == -1) {
				avl[index].rightNode = newNode(x, index);
				fix_depth(index);
			}
			else {
				rec_insert(x, avl[index].rightNode);
			}
		}
		else if (avl[index].value > x) {
			if (avl[index].leftNode == -1) {
				avl[index].leftNode = newNode(x, index);
				fix_depth(index);
			}
			else {
				rec_insert(x, avl[index].leftNode);
			}
		}
		return;
	}

	void eraseByIndex(int index) {
		if (index == -1) {
			return;
		}
		if (avl[index].rightNode == -1) {
			if (index != 0) {
				int prevIndex = avl[index].prev;
				emptyNodes.push(index);
				if (avl[prevIndex].leftNode == index) {
					avl[prevIndex].leftNode = avl[index].leftNode;
				}
				else {
					avl[prevIndex].rightNode = avl[index].leftNode;
				}
				if (avl[index].leftNode != -1) {
					avl[avl[index].leftNode].prev = prevIndex;
				}
				fix_depth(prevIndex);
			}
			else {
				if (avl[0].leftNode == -1) {
					avl.clear();
					emptyNodes = stack<int>();
				}
				else {
					emptyNodes.push(avl[0].leftNode);
					avl[0] = avl[avl[0].leftNode];
					avl[0].prev = -1;
					if (avl[0].rightNode != -1) avl[avl[0].rightNode].prev = 0;
					if (avl[0].leftNode != -1) avl[avl[0].leftNode].prev = 0;
				}
			}
		}
		else if (avl[index].leftNode == -1) {
			if (index != 0) {
				int prevIndex = avl[index].prev;
				emptyNodes.push(index);
				if (avl[prevIndex].leftNode == index) {
					avl[prevIndex].leftNode = avl[index].rightNode;
				}
				else {
					avl[prevIndex].rightNode = avl[index].rightNode;
				}
				if (avl[index].rightNode != -1) {
					avl[avl[index].rightNode].prev = prevIndex;
				}
				fix_depth(prevIndex);
			}
			else {
				if (avl[0].rightNode == -1) {
					avl.clear();
					emptyNodes = stack<int>();
				}
				else {
					emptyNodes.push(avl[0].rightNode);
					avl[0] = avl[avl[0].rightNode];
					avl[0].prev = -1;
					if (avl[0].rightNode != -1) avl[avl[0].rightNode].prev = 0; 
					if (avl[0].leftNode != -1) avl[avl[0].leftNode].prev = 0;
				}
			}
		}
		else {
			int search = avl[index].rightNode;
			while (avl[search].leftNode != -1) {
				search = avl[search].leftNode;
			}
			avlSwap(index, search);
			eraseByIndex(search);
		}
	}
	
public:

	void insert(int x) {
		rec_insert(x, 0);
	}

	void erase(int x) {
		if (!avl.empty()) {
			eraseByIndex(rec_find(x, 0));
		}
	}

	bool find(int x) {
		if (!avl.empty()) {
			return (rec_find(x, 0) != -1);
		}
		return 0;
	}

	int next(int x) {
		if (!avl.empty()) {
			return rec_next(x, 0);
		}
		return INT_MAX;
	}

	int prev(int x) {
		if (!avl.empty()) {
			return rec_prev(x, 0);
		}
		return INT_MIN;
	}

};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	AVL avl;
	string command;
	int x;
	vector <string> ans;
	while (cin >> command >> x) {
		if (command == "insert") {
			avl.insert(x);
		}
		else if (command == "delete") {
			avl.erase(x);
		}
		else if (command == "exists") {
			ans.push_back(avl.find(x) ? "true" : "false");
		}
		else if (command == "next") {
			int n = avl.next(x);
			ans.push_back(n == INT_MAX ? "none" : to_string(n));
		}
		else if (command == "prev") {
			int p = avl.prev(x);
			ans.push_back(p == INT_MIN ? "none" : to_string(p));
		}
	}
	for (int i = 0; i < ans.size(); ++i) {
		std::cout << ans[i] << '\n';
	}
}
