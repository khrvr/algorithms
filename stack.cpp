#include <string>
#include <vector>
#include <iostream>
#include <optional>

using namespace std;

class node {
	// появилась приватная часть
private:
	long long val = 0;
	long long size = 0;
	node* prev = nullptr;
	node* top = nullptr;
public:
	// добавил деструктор
	~node() {
		delete top;
		delete prev;
	}
	void push(long long inputNumber) {
		node* element = new node();
		if (top != nullptr) {
			element->size = (top->size) + 1;
		}
		else {
			element->size = 1;
		}
		element->val = inputNumber;
		element->prev = top;
		top = element;
	}
	auto pop() {
		long long answer;
		long long check = 0;
		if (top != nullptr) {
			check = 1;
			answer = top->val;
			top = top->prev;
		}
		// использую optional 
		return check == 1 ? optional <long long> {answer} : nullopt;
	}
	auto back() {
		return (top != nullptr) ? optional <long long> {top->val} : nullopt;
	}
	void clear() {
		while (top != nullptr) {
			top = top->prev;
		}
	}
	long long stackSize() {
		if (top != nullptr) {
			return top->size;
		}
		else {
			return 0;
		}
	}
};

int main() {
	string input;
	long long inputNumber;
	vector <pair <string, long long>> answer;
	string first;
	pair <string, long long> result;
	node stack;
	// теперь все через else if
	while (true) {
		cin >> input;
		if (input == "exit") {
			stack.clear();
			answer.push_back(make_pair("bye", -1));
			break;
		}
		else if (input == "push") {
			cin >> inputNumber;
			stack.push(inputNumber);
			answer.push_back(make_pair("ok", -1));
		}
		else if (input == "pop") {
			if (auto ans = stack.pop()) {
				answer.push_back(make_pair("number", *ans));
			}
			else {
				answer.push_back(make_pair("error", -1));
			}
		}
		else if (input == "back") {
			if (auto ans = stack.back()) {
				answer.push_back(make_pair("number", *ans));
			}
			else {
				answer.push_back(make_pair("error", -1));
			}
	    }
		else if (input == "size") {
			answer.push_back(make_pair("number", stack.stackSize()));
		}
		else {
		    stack.clear();
			answer.push_back(make_pair("ok", -1));
		}
	}
	for (long long i = 0; i < answer.size(); i++) {
		if (answer[i].first == "number") {
			cout << answer[i].second << endl;
		}
		else {
			cout << answer[i].first << endl;
		}
	}
}
