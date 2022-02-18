
//номер посылки - 146868166

#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

//dp - для каждого i от 0 до n храним количество мирных множеств с силами 0, 1, ... n и 
//наибольшим элементом i
//База - множества с наибольшим элементом 0
//Формула пересчета - для множества с наибольшим элементом i и силой i ответ очевиден, 
//для других же значений j перебираем возможный размер второго наибольшего элемента после j 
//Порядок пересчета - возрастание i и возрастание j
//Ответ - сумма количества множеств силы n с наибольшими элементами 0, 1, ... n

long long largestSet(int n) {
	vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
	for (int i = 1; i < n + 1; ++i) {
		dp[i][i] = 1;
		for (int j = i + 1; j < n + 1; ++j) {
			int wantedSum = std::max(0, j - i);
			for (int q = 0; q <= i / 2; ++q) {
				dp[i][j] += dp[q][wantedSum];
			}
		}
	}
	long long ans = 0;
	for (int i = 0; i < n + 1; ++i) {
		ans += dp[i][n];
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n;
	std::cin >> n;
	std::cout << largestSet(n);
}
