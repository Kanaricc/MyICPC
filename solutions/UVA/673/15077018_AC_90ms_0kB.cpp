#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
	string kases; getline(cin, kases);
	int kase = stoi(kases);
	while (kase--) {
		string inp;
		getline(cin, inp);
		stack<char> stk;
		bool ok = true;
		for (int i = 0; i < inp.size(); i++) {
			if (inp[i] == '[' || inp[i] == '(')stk.push(inp[i]);
			else {
				if (stk.empty()) {
					ok = false;
					break;
				}

				if (inp[i] == ']' && stk.top() == '[') {
					stk.pop();
				}
				else if (inp[i] == ')' && stk.top() == '(') {
					stk.pop();
				}
				else {
					ok = false;
					break;
				}
			}
		}
		if (!stk.empty())ok = false;
		cout << (ok ? "Yes" : "No") << endl;
	}

	//while (1);
	return 0;
}