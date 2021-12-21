
//131965780 - посылка 

#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::vector;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::swap;

class binHeap {

	vector <long long> heap = {-1};
	map <long long, long long> pointer;
	vector <long long> num = {-1};
	long long operation = 0;

	void exchange(long long index1, long long index2) {
		swap(pointer[num[index1]], pointer[num[index2]]);
		swap(num[index1], num[index2]);
		swap(heap[index1], heap[index2]);
	}

	long long minChild(long long current) const {
		if (2 * current + 1 >= heap.size()) {
			return (2 * current);
		}
		if (heap[2 * current + 1] < heap[2 * current]) {
			return (2 * current + 1);
		}
		return (2 * current);
	}

	void siftDown() {
		long long current = 1;
		long long min;
		while (current * 2 < heap.size()) {
			min = minChild(current);
			if (heap[current] > heap[min]) {
				exchange(current, min);
				current = min;
			}
			else {
				break;
			}
		}
	}

	void siftUp(long long index) {
		long long current = index;
		while (current / 2 > 0) {
			if (heap[current] < heap[current / 2]) {
				exchange(current, current / 2);
				current = current / 2;
			}
			else {
				break;
			}
		}
	}

public:

	void insert(long long x) {
		++operation;
		heap.push_back(x);
		num.push_back(operation);
		pointer[operation] = heap.size() - 1;
		siftUp(heap.size() - 1);
	}

	long long getMin() {
		++operation;
		return heap[1];
	}

	void extractMin() {
		++operation;
		exchange(1, heap.size() - 1);
		pointer.erase(num[heap.size() - 1]);
		heap.pop_back();
		num.pop_back();
		siftDown();
	}

	void decreaseKey(long long ii, long long delta) {
		++operation;
		heap[pointer[ii]] = heap[pointer[ii]] - delta;
		siftUp(pointer[ii]);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	long long q;
	cin >> q;
	string input;
	long long x, ii, delta;
	binHeap hippie;
	vector <long long> answer;
	for (long long j = 0; j < q; ++j) {
		cin >> input;
		if (input == "decreaseKey") {
			cin >> ii >> delta;
			hippie.decreaseKey(ii, delta);
		}
		else if (input == "getMin") {
			answer.push_back(hippie.getMin());
		}
		else if (input == "extractMin") {
			hippie.extractMin();
		}
		else if (input == "insert") {
			cin >> x;
			hippie.insert(x);
		}
	}
	for (auto& j : answer) {
		cout << j << '\n';
	}
}
