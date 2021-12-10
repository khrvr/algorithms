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

void partition(int pivot, vector <int>& arr, vector <int>& part_arr, char c) {
	int check = 0;
	if (c == '<') {
		check = 1;
	}
	else if (c == '>') {
		check = -1;
	}
	for (int i = 0; i < arr.size(); ++i) {
		if (sign(pivot - arr[i]) == check) {
			part_arr.push_back(arr[i]);
		}
	}
}

void quickSort(vector <int>& arr) {
	int pivot;
	vector <int> part_arr;
	vector <int> part_arrC;
	if (arr.size() > 1) {
		pivot = arr[rand() % arr.size()];
		partition(pivot, arr, part_arr, '<');
		quickSort(part_arr);
		partition(pivot, arr, part_arr, '=');
		partition(pivot, arr, part_arrC, '>');
		quickSort(part_arrC);
		arr = move(part_arr);
		arr.insert(arr.end(), part_arrC.begin(), part_arrC.end());
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
	quickSort(arr);
	for (int i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
}
