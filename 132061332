#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <long long> lsd(vector <long long> numbers) {
	for (int digit = 0; digit < 8; ++digit) {
		vector <int> countArr(256, 0);
		vector <long long> answers(numbers.size(), 0);
		for (int i = 0; i < numbers.size(); ++i) {
			countArr[((numbers[i]) >> digit * 8)&0xff]++;
		}
		for (int i = 1; i < 256; ++i) {
			countArr[i] += countArr[i - 1];
		}
		for (int i = numbers.size() - 1; i >= 0; --i) {
			answers[--countArr[((numbers[i]) >> digit * 8)&0xff]] = numbers[i];
		}
		numbers = move(answers);                                                                          
	}
	return numbers;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	long long n;
	cin >> n;
	vector <long long> numbers;
	long long input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		numbers.push_back(input);
	}
	numbers = lsd(numbers);
	reverse(numbers.begin(), numbers.end());
	for (int i = numbers.size() - 1; i >= 0; --i) {
		cout << numbers[i] << " ";
	}
} 
