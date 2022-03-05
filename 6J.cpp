
//посылка - 148442522

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

//dp - для каждого столбца и каждой маски храним количество узоров с таким количеством столбцов, заканчивающихся этой маской
//База - первый столбец - просто 1 для каждого узора
//Формула пересчета - проходим по всем маскам w, если наша маска и следующая маска вместе не дают квадрат 2 * 2, то dp[i + 1][w] += dp[i][j]
//Порядок пересчета - идем по стобцам, потом по маскам
//Ответ - сумма dp[columns - 1][?]

bool noSquare(int mask1, int mask2, int length) {
	int previousMatched = -1;
	if (mask1 % 2 == mask2 % 2) previousMatched = (mask1 % 2);
	for (int i = 1; i < length; ++i) {
		mask1 /= 2;
		mask2 /= 2;
		if (mask1 % 2 != mask2 % 2) previousMatched = -1;
		else if (previousMatched == mask1 % 2) return false;
		else previousMatched = mask1 % 2;
	}
	return true;
}

int getAmount(int lines, int columns) {
	int lineComb = (1 << lines);
	vector<vector<int>> dp(columns, vector<int>(lineComb, 0));
	dp[0] = vector<int>(lineComb, 1);
	for (int i = 0; i < columns - 1; ++i) {
		for (int j = 0; j < lineComb; ++j) {
			for (int w = 0; w < lineComb; ++w) {
				if (noSquare(j, w, lines)) dp[i + 1][w] += dp[i][j];
			}
		}
	}
	int amount = 0;
	for (int j = 0; j < lineComb; ++j) amount += dp[columns - 1][j];
	return amount;
}

signed main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	int columns = std::max(n, m);
	int lines = std::min(n, m);
	std::cout << getAmount(lines, columns);
}
