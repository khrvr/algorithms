#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class binHeap {

private:

	vector <long long> heap;
	map <long long, long long> pointer;
	vector <long long> num;

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
  
  void topSiftDown() {
		long long current = 1;
		long long min;
		while (current * 2 < heap.size()) {
			min = minNode(current);
			if (heap[current] > heap[min]) {
				exchange(current, min);
				current = min;
			}
			else {
				break;
			}
		}
	}
  
  void exchange(long long index1, long long index2) {
		swap(pointer[num[index1]], pointer[num[index2]]);
		swap(num[index1], num[index2]);
		swap(heap[index1], heap[index2]);
	}

	long long minNode(long long current) {
		if (2 * current + 1 >= heap.size()) {
			return (2 * current);
		}
		else {
			if (heap[2 * current + 1] < heap[2 * current]) {
				return (2 * current + 1);
			}
			else {
				return (2 * current);
			}
		}
	}
  
public:

	binHeap() {
		heap = {-1};
		num = {-1};
	}
  
	void insert(long long x, long long counter) {
		heap.push_back(x);
		num.push_back(counter);
		pointer[counter] = heap.size() - 1;
		siftUp(heap.size() - 1);
	}

	long long getMin() {
		return heap[1];
	}

	void extractMin() {
		exchange(1, heap.size() - 1);
		pointer.erase(num[heap.size() - 1]);
		heap.pop_back();
		num.pop_back();
		topSiftDown();
	}

	void decreaseKey(long long ii, long long delta) {
		heap[pointer[ii]] = heap[pointer[ii]] - delta;
		siftUp(pointer[ii]);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	long long q;
	cin >> q;
	string input;
	long long xcounter = 0;
	long long x, ii, delta;
	binHeap *hippie = new binHeap();
	vector <long long> answer;
	for (long long j = 0; j < q; ++j) {
		cin >> input;
		++xcounter;
		if (input == "decreaseKey") {
			cin >> ii >> delta;
			hippie->decreaseKey(ii, delta);
		}
		else if (input == "getMin") {
			answer.push_back(hippie->getMin());
		}
		else if (input == "extractMin") {
			hippie->extractMin();
		}
		else if (input == "insert") {
			cin >> x;
			hippie->insert(x, xcounter);
		}
	}
	for (auto& j: answer) {
		cout << j << '\n';
	}
}
