#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

pair<int, int> partition(vector <int>& arr, int start, int end, int pivot) {
	int numOfElem1 = 0;
	int arrIndex = start;
	for (int i = start; i < end; ++i) {
		if (arr[i] < pivot) {
			swap(arr[i], arr[arrIndex++]);
			++numOfElem1;
		}
	}
	int numOfElem2 = 0;
	for (int i = start + numOfElem1; i < end; ++i) {
		if (arr[i] == pivot) {
			swap(arr[i], arr[arrIndex++]);
			++numOfElem2;
		}
	}
	return { numOfElem1, numOfElem2 };
}

void quickSort(vector <int>& arr, int start, int end) {
	if (end - start > 1) {
		int pivot = arr[start + rand() % (end - start)];
		pair<int, int> numOfElem = partition(arr, start, end, pivot);
		quickSort(arr, start, start + numOfElem.first);
		quickSort(arr, start + numOfElem.first + numOfElem.second, end);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector <int> arr;
	int input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		arr.push_back(input);
	}
	quickSort(arr, 0, n);
	for (int i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
}
