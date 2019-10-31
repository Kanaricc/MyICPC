#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

priority_queue<int> number;
bool solve(int n, int k) {
	int base = 1;
	for (n; n; n >>= 1) {
		if (n & 1)number.push(base);
		base *= 2;
	}
	while (number.size() < k) {
		int big = number.top();
		number.pop();
		if (big == 1)return false;

		number.push(big / 2);
		number.push(big / 2);
	}

	return number.size()==k;
}
stack<int> temp;
int main() {
	ios::sync_with_stdio(false);
	int n, k; cin >> n >> k;
	if (solve(n, k)) {
		cout << "YES" << endl;
		while (!number.empty()) {
			int n = number.top();
			number.pop();
			temp.push(n);
		}
		while (!temp.empty()) {
			cout << temp.top() << " ";
			temp.pop();
		}
		cout << endl;
	}
	else cout << "NO" << endl;

	//while (1);
	return 0;
}