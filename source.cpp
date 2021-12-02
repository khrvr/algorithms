#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <utility>

using namespace std;

long long mergeSort( vector <long long> arr) {
	queue <long long> empty;
	vector <queue <long long>> arrDivided1 (arr.size(), empty);
	for (long long i = 0; i < arr.size(); i++) {
		arrDivided1[i].push(arr[i]);
	}
	long long answer = 0;
	long long counter = -1;
	while (arrDivided1.size() != 1) {
		// инициализировал вектор в цикле
		vector <queue <long long>> arrDivided2;
		counter = -1;
		for (long long i = 0; i < arrDivided1.size(); i += 2) {
			counter++;
			if (i == (arrDivided1.size() - 1)) {
				arrDivided2.push_back(arrDivided1[arrDivided1.size() - 1]);
			}
			else {
				arrDivided2.push_back(empty);
				// добавил auto  
				auto& first = arrDivided1[i];
				auto& second = arrDivided1[i + 1];
				auto& merge = arrDivided2[counter];
				for (long long e = 0; (!first.empty()) || (!second.empty()); e++) {
					if (first.empty()) {
						while (!second.empty()) {
							merge.push(second.front());
							second.pop();
						}
						break;
					}
					else if (second.empty()) {
						while (!first.empty()) {
							merge.push(first.front());
							first.pop();
						}
						break;
					}
					else if (first.front() > second.front()) {
						answer += first.size();
						merge.push(second.front());
						second.pop();
					}
					else {
						merge.push(first.front());
						first.pop();
					}
				}
			}
		}
		// move вместо clear
		arrDivided1 = move(arrDivided2);
	}

	return answer;
}
int main() {
	ifstream cin("inverse.in");
	ofstream cout("inverse.out");
	long long n;
	cin >> n;
	long long input;
	vector <long long> arr;
	for (long long i = 0; i < n; ++i) {
		cin >> input; 
		arr.push_back(input);
	}
	cout << mergeSort(arr);
}
