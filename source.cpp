#include <iostream>
#include <vector>
#include <stdio.h>
#include <random>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, k;
	cin >> n >> k;
	vector <int> arr;
	int input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		arr.push_back(input);
	}
	int pivot = 0;
	vector <int> partition;
	int counter = -1;
	while (arr.size() > 1) {
		pivot = arr[rand() % arr.size()];
		partition.clear();
		counter = -1;
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] < pivot) {
				partition.push_back(arr[i]);
				++counter;
			}
		}
		if (counter >= k) {
			arr = move(partition);
			continue;
		}
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] == pivot) {
				partition.push_back(arr[i]);
				++counter;
			}
		}
		if (counter >= k) {
			cout << pivot;
			return 0;
		}
		k = k - counter - 1;
		partition.clear();
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] > pivot) {
				partition.push_back(arr[i]);
			}
		}
		arr = move(partition);
	}
	cout << arr[0];
}
