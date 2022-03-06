
//номер посылки - 148590439

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::vector;

static const int mod = 1000000007;

bool maskFits(int mask, const vector<int>& temp) {
	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i] != -1 && temp[i] != (mask & 1)) return false;
		mask /= 2;
	}
	return true;
}

int calculateNewBit(int curBit, int prevBit, int prevTakenBit, int& mask) {
	int tmp = 2 - curBit - prevBit - prevTakenBit;
	if (tmp < 0 || tmp > 1) mask = -1;
	return tmp;
}

int vecToFittingMask(const vector<bool>& newMask, const vector<int>& temp) {
	int maskSize = newMask.size();
	int mask = 0;
	for (int i = 0; i < maskSize; ++i) {
		if (newMask[i]) mask += (1 << i);
	}
	if (!maskFits(mask, temp)) mask = -1;
	return mask;
}

std::pair<int, int> masksThatFit(int mask, const vector<int>& temp, int maskSize) {
	vector<bool> newMask0(maskSize, 0);
	vector<bool> newMask1(maskSize, 1);
	int mask0 = 0;
	int mask1 = 0;
	int prevBit = (mask & 1);
	mask /= 2;
	for(int i = 1; i < maskSize; ++i) {
		int curBit = (mask & 1);
		newMask0[i] = calculateNewBit(curBit, prevBit, newMask0[i - 1], mask0);
		newMask1[i] = calculateNewBit(curBit, prevBit, newMask1[i - 1], mask1);
		mask /= 2;
		prevBit = curBit;
	}
	if (mask0 != -1) mask0 = vecToFittingMask(newMask0, temp);
	if (mask1 != -1) mask1 = vecToFittingMask(newMask1, temp);
	return { mask0, mask1 };
}

//dp - для каждого столбца i и для каждой маски mask храним количество вариантов наслать голод на страну от 1 
//до i столбца так, чтобы i столбец голодал как ему велит mask
//База - первый столбец - 1 для масок, подходящих под заданные условия
//Формула пересчета - легко понять, что для каждой маски есть не более 2, следующих за ней. 
//Тогда dp[column][newMask] += dp[column - 1][mask]
//Порядок пересчета - идем по столбцам, в каждой итерации цикла - по маскам
//Ответ - сумма dp[columns - 1][?]

int getAmount(const vector<vector<int>>& columns, int n, int m) {
	vector<vector<int>> dp(m, vector<int>((1 << n), 0));
	for (int mask = 0; mask < (1 << n); ++mask) {
		if (maskFits(mask, columns[0])) dp[0][mask] = 1;
	}
	for (int column = 1; column < m; ++column) {
		for (int mask = 0; mask < (1 << n); ++mask) {
			std::pair<int, int> nextMasks = masksThatFit(mask, columns[column], n);
			if (nextMasks.first >= 0) (dp[column][nextMasks.first] += dp[column - 1][mask]) %= mod;
			if (nextMasks.second >= 0) (dp[column][nextMasks.second] += dp[column - 1][mask]) %= mod;
		}
	}
	int ans = 0;
	for (int mask = 0; mask < (1 << n); ++mask) {
		(ans += dp[m - 1][mask]) %= mod;
	}
	return ans;
}

signed main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, m;
	std::string input;
	std::cin >> n >> m;
	vector<vector<int>> columns(m, vector<int>(n, -1));
	for (int i = 0; i < n; ++i) {
		std::cin >> input;
		for (int j = 0; j < m; ++j) {
			if (input[j] == '+') columns[j][i] = 1;
			else if (input[j] == '-') columns[j][i] = 0;
		}
	}
	std::cout << getAmount(columns, n, m);
}
