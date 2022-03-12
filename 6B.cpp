
//номер посылки - 149398158	

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

static const long long mod = 1000000007;

struct prob {
	long long p;
	long long q;
	bool odd;

	prob(long long p, long long q, bool odd) : p(p), q(q), odd(odd) {}
};

prob recalcProb(prob first, prob second) {
	long long p;
	if (!first.odd) p = (mod + first.p * second.q - second.p) % mod;
	else p = (first.p * second.q + second.p) % mod;
	long long q = (first.q * second.q) % mod;
	p = (mod + q - p) % mod;
	q = (2 * q) % mod;
	bool odd = first.odd ^ second.odd;
	return prob(p, q, odd);
}

prob getProbByElement(long long lastElem, int sz, vector<prob>& dp) {
	if (lastElem == 1) return dp[sz];
	if (lastElem % 2) {
		prob newProb = getProbByElement(lastElem - 1, sz, dp);
		return recalcProb(newProb, dp[sz]);
	}
	prob newProb = getProbByElement(lastElem / 2, sz, dp);
	return recalcProb(newProb, newProb);
}

//dp - для каждого i храним искомую вероятность при использовании только первых i элементов a
//База - вероятность для 1 хода - 0/1
//Пересчет - делается быстрой рекурсией за log функцией getProbByElement
//Ответ - последний элемент dp


prob getProb(vector<long long> a) {
	int k = a.size();
	vector<prob> dp;
	dp.push_back(prob(0, 1, 1));
	for (int i = 0; i < k; ++i) {
		dp.push_back(getProbByElement(a[i], i, dp));
	}
	return dp[k];
}

signed main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int k;
	std::cin >> k;
	vector<long long> a(k);
	for (int i = 0; i < k; ++i) {
		std::cin >> a[i];
	}
	prob ans = getProb(a);
	std::cout << ans.p << "/" << ans.q;
}
