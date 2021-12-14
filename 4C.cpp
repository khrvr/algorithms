
//138103120 - номер посылки 

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
	int subtree = 0;
	Node(int x, int previous) : value(x), prev(previous) {}
	Node() = default;
	void operator=(const Node& other) {
		value = other.value;
		depth = other.depth;
		prev = other.prev;
		subtree = other.subtree;
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
				avl[prn].subtree -= (avl[avl[prn].leftNode].subtree + 1);
				swap(avl[index].leftNode, avl[avl[index].rightNode].leftNode);
				avl[avl[index].leftNode].prev = index;
				int current = avl[avl[index].rightNode].leftNode;
				if (current != -1) {
					avl[current].prev = avl[index].rightNode;
					avl[avl[index].rightNode].subtree += (avl[current].subtree + 1);
				}
				avlSwap(index, avl[index].leftNode);
				swap(avl[avl[index].leftNode].leftNode, avl[avl[index].leftNode].rightNode);
				swap(avl[avl[index].rightNode].leftNode, avl[avl[index].leftNode].leftNode);
				current = avl[avl[index].leftNode].leftNode;
				if (current != -1) {
					avl[current].prev = avl[index].leftNode;
					avl[avl[index].rightNode].subtree -= (avl[current].subtree + 1);
					avl[avl[index].leftNode].subtree += (avl[current].subtree + 1);
				}
				current = avl[avl[index].rightNode].leftNode;
				if (current != -1) {
					avl[current].prev = avl[index].rightNode;
					avl[avl[index].leftNode].subtree -= (avl[current].subtree + 1);
					avl[avl[index].rightNode].subtree += (avl[current].subtree + 1);
				}
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
				if (avl[index].rightNode != -1) {
					avl[avl[index].rightNode].prev = index;
					avl[avl[index].leftNode].subtree -= (avl[avl[index].rightNode].subtree + 1);
				}
				if (avl[avl[index].leftNode].leftNode != -1) {
					avl[avl[avl[index].leftNode].leftNode].prev = avl[index].leftNode;
					avl[avl[index].leftNode].subtree += (avl[avl[avl[index].leftNode].leftNode].subtree + 1);
				}
				fix_depth(avl[index].leftNode);
			}
		}
		else if (deltaIndex == 2) {
			if (delta(pln) == -1) {
				avl[pln].subtree -= (avl[avl[pln].rightNode].subtree + 1);
				swap(avl[index].rightNode, avl[avl[index].leftNode].rightNode);
				avl[avl[index].rightNode].prev = index;
				int current = avl[avl[index].leftNode].rightNode;
				if (current != -1) {
					avl[current].prev = avl[index].leftNode;
					avl[avl[index].leftNode].subtree += (avl[current].subtree + 1);
				}
				avlSwap(index, avl[index].rightNode);
				swap(avl[avl[index].rightNode].rightNode, avl[avl[index].rightNode].leftNode);
				swap(avl[avl[index].leftNode].rightNode, avl[avl[index].rightNode].rightNode);
				current = avl[avl[index].rightNode].rightNode;
				if (current != -1) {
					avl[current].prev = avl[index].rightNode;
					avl[avl[index].leftNode].subtree -= (avl[current].subtree + 1);
					avl[avl[index].rightNode].subtree += (avl[current].subtree + 1);
				}
				current = avl[avl[index].leftNode].rightNode;
				if (current != -1) {
					avl[current].prev = avl[index].leftNode;
					avl[avl[index].rightNode].subtree -= (avl[current].subtree + 1);
					avl[avl[index].leftNode].subtree += (avl[current].subtree + 1);
				}
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
				if (avl[index].leftNode != -1) {
					avl[avl[index].leftNode].prev = index;
					avl[avl[index].rightNode].subtree -= (avl[avl[index].leftNode].subtree + 1);
				}
				if (avl[avl[index].rightNode].rightNode != -1) {
					avl[avl[avl[index].rightNode].rightNode].prev = avl[index].rightNode;
					avl[avl[index].rightNode].subtree += (avl[avl[avl[index].rightNode].rightNode].subtree + 1);
				}
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
		--avl[index].subtree;
		if (avl[index].value < x) {
			return rec_find(x, avl[index].rightNode);
		}
		else if (avl[index].value > x) {
			return rec_find(x, avl[index].leftNode);
		}
		return index;
	}

	void rec_insert(int x, int index) {
		++avl[index].subtree;
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
			--avl[search].subtree;
			while (avl[search].leftNode != -1) {
				search = avl[search].leftNode;
				--avl[search].subtree;
			}
			avlSwap(index, search);
			eraseByIndex(search);
		}
	}

	int rec_getk(int index, int k) {
		int pln = avl[index].leftNode;
		int prn = avl[index].rightNode;
		if (prn != -1) {
			if (avl[prn].subtree + 1 >= k) {
				return rec_getk(prn, k);
			}
			else if (avl[prn].subtree + 1 == k - 1) {
				return avl[index].value;
			}
			else {
				return rec_getk(pln, k - avl[prn].subtree - 2);
			}
		}
		else {
			if (k == 1) {
				return avl[index].value;
			}
			else {
				return rec_getk(pln, k - 1);
			}
		}
	}

public:

	void insert(int x) {
		if (avl.empty()) {
			avl.push_back(Node(x, -1));
			return;
		}
		rec_insert(x, 0);
	}

	void erase(int x) {
		if (!avl.empty()) {
			eraseByIndex(rec_find(x, 0));
		}
	}

	int getk(int k) {
		return rec_getk(0, k);
	}

	void print() {
		cout << '\n';
		for (int i = 0; i < avl.size(); ++i) {
			cout << avl[i].leftNode << " " << avl[i].rightNode << " " << avl[i].subtree << '\n';
		}
	}

};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	AVL avl;
	int n, command, k;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> command >> k;
		if (command == 1) {
			avl.insert(k);
		}
		else if (command == -1) {
			avl.erase(k);
		}
		else if (command == 0) {
			cout << avl.getk(k) << '\n';
		}
	}
}
