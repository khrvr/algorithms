
//номер посылки - 146866866

#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

int f(int i) {
	return (i & (i + 1));
}

int g(int i) {
	return (i | (i + 1));
}

pair<int, int> getPrefMax(const vector<pair<int, int>>& fentree, int index) {
	pair<int, int> answer = { INT_MIN, INT_MIN };
	for (int i = index; i >= 0; i = f(i) - 1) answer = std::max(answer, fentree[i]);
	return answer;
}

void update(vector<pair<int, int>>& fentree, int index, int val) {
	for (int i = index; i < fentree.size(); i = g(i)) {
		fentree[i] = std::max(fentree[i], std::make_pair(val, index));
	}
}

//База - пустое дерево Фенвика, в котором для каждого элемента длина наибольшей НВП = INT_MIN
//Формула пересчета - наибольшая длина НВП до среды меньших элементов с меньшим индексом + 1
//Порядок пересчета - элементы по возрастанию
//Ответ - наибольшее число среди всех

void lds(const vector<int>& inp, vector<int>& ans) { //largest decreasing subsequence
	int inpSz = inp.size();
	vector<pair<int, int>> sortedInp(inpSz);
	for (int i = 0; i < inpSz; ++i) {
		sortedInp[inpSz - 1 - i] = {inp[i], inpSz - 1 - i};
	}
	sort(sortedInp.begin(), sortedInp.end());
	vector<pair<int, int>> fentree(inpSz, { INT_MIN, INT_MIN }), changes(inpSz);
	for (int i = 0; i < inpSz; ++i) {
		pair<int, int> tmp = getPrefMax(fentree, sortedInp[i].second);
		changes[i] = tmp;
		update(fentree, sortedInp[i].second, std::max(1, 1 + tmp.first));
	}
	vector<int> placeInSorted(inpSz);
	for (int i = 0; i < inpSz; ++i) {
		placeInSorted[sortedInp[i].second] = i;
	}
	pair<int, int> elem = getPrefMax(fentree, inpSz - 1);
	ans.resize(elem.first);
	int ansIndex = 0;
	while (elem.second >= 0) {
		ans[ansIndex] = inpSz - elem.second;
		++ansIndex;
		elem = changes[placeInSorted[elem.second]];
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n;
	std::cin >> n;
	vector<int> a(n), ans;
	for (int& i : a) std::cin >> i;
	lds(a, ans);
	std::cout << ans.size() << std::endl;
	for (int& i : ans) std::cout << i << " ";
}
