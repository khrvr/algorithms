#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class line {
private:
	queue <int> firstQueue; 
	queue <int> secondQueue; 
	stack <int> privilegedStack; 
public:
	void addPrivileged(int i) {
		while (firstQueue.size() < secondQueue.size() + firstQueue.size() + privilegedStack.size() - (secondQueue.size() + firstQueue.size() + privilegedStack.size()) / 2) {
			if (privilegedStack.empty()) {
				firstQueue.push(secondQueue.front());
				secondQueue.pop();
			}
			else {
				firstQueue.push(privilegedStack.top());
				privilegedStack.pop();
			}
		}
		privilegedStack.push(i);
	}
	void addOrdinary(int i) {
		secondQueue.push(i);
	}
	int goblinLeaves() {
		if (firstQueue.empty()) {
			if (privilegedStack.empty()) {
				firstQueue.push(secondQueue.front());
				secondQueue.pop();
			}
			else {
				firstQueue.push(privilegedStack.top());
				privilegedStack.pop();
			}
		}
		int answer = firstQueue.front();
		firstQueue.pop();
		return answer;
	}
};

int main() {
	int N = 0;
	cin >> N;
	char input = 'q'; 
	int inputi = 0; 
	vector <int> answers; 
	line goblinLine;
	for( int i = 0; i < N; i++ ) {
		cin >> input;
		if( input == '-' ) {
			answers.push_back(goblinLine.goblinLeaves());
		}
		else if( input == '+' ) {
				cin >> inputi;
				goblinLine.addOrdinary(inputi);
		}
		else {
			cin >> inputi;
			goblinLine.addPrivileged(inputi);
		}	
	}
	for( int i = 0; i < answers.size(); i++ ) {
		cout << answers[i] << "\n";
	}
}
