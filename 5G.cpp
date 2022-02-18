
//номер послыки - 146872462

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

//dp - для каждой пары элементов из первого и второго массивов храним длину НОП соответствующих префиксов
//База - первый элемент первого массива и каждый из элементов вторго массива
//Формула пересчета - если соответствующие элементы совпадают, можем убрать оба и к предыдущему значению добавить 1,
//в противном случае уменьшаем либо один индекс, либо другой и берем максимум. Так как нас интересуют только последние два 
//рассмотренных элемента первого массива, можно хранить не двумерный массив, а dp и prev
//Порядок пересчета - по индексу первого массива
//Ответ - последний элемент dp - НОП на префиксах, совпадающих со всеми массивами


int lcs(const vector<int>& first, const vector<int>& second) {
	int fsz = first.size(), ssz = second.size();
	vector<int> dp(ssz, 1), prev(ssz);
	for (int j = 0; j < ssz; ++j) {
		if (first[0] != second[j]) dp[j] = 0;
		else break;
	}
	for (int i = 1; i < fsz; ++i) {
		prev.swap(dp);
		if (first[i] == second[0]) dp[0] = 1;
		else dp[0] = prev[0];
		for (int j = 1; j < ssz; ++j) {
			if (first[i] == second[j]) dp[j] = prev[j - 1] + 1;
			else dp[j] = std::max(dp[j - 1], prev[j]);
		}
	}
	return dp[ssz - 1];
}

int main() {
	std::ios_base::sync_with_stdio("false");
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, m;
	std::cin >> n;
	vector<int> a(n);
	for (int& i : a) std::cin >> i;
	std::cin >> m;
	vector<int> b(m);
	for (int& i : b) std::cin >> i;
	std::cout << lcs(a, b);
}
