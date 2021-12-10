#include <iostream>
#include <vector>
#include <stdio.h>
#include <random>

using namespace std;

int sign(int a) {
	if (a == 0) {
		return 0;
	}
	else if (a < 0) {
		return -1;
	}
	else {
		return 1;
	}
}

int partition(int pivot, vector <int>& arr, vector <int>& part_arr, char c) {
	int check = 0;
	if (c == '<') {
		check = 1;
	}
	else if (c == '>') {
		check = -1;
	}
	int numberOfElements = 0;
	for (int i = 0; i < arr.size(); ++i) {
		if (sign(pivot - arr[i]) == check) {
			part_arr.push_back(arr[i]);
			++numberOfElements;
		}
	}
	return numberOfElements;
}

int quickSelect(int k, vector <int> arr) {
	int pivot = 0;
	vector <int> part_arr;
	int counter = -1;
	while (arr.size() > 1) {
		pivot = arr[rand() % arr.size()];
		part_arr.clear();
		counter = -1;
		counter += partition(pivot, arr, part_arr, '<');
		if (counter >= k) {
			arr = move(part_arr);
			continue;
		}
		counter += partition(pivot, arr, part_arr, '=');
		if (counter >= k ) {
			return pivot;
		}
		k = k - counter - 1;
		part_arr.clear();
		partition(pivot, arr, part_arr, '>');
		arr = move(part_arr);
	}
	return arr[0];
}

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
	cout << quickSelect(k, arr);
}
