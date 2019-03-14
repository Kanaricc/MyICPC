#include <iostream>
#include <stack>
using namespace std;
const int MAXN = 1010;


int inp[MAXN], n;
int main() {
	int kase = 0;
	while (cin >> n) {
		if (n == 0)break;
		if(kase) cout << endl;
		kase++;
		while (1) {
			for (int i = 0; i < n; i++) {
				cin >> inp[i];
				if (inp[i] == 0) {
					goto br1;
				}
			}

			stack<int> stk;

			int lptr = 0, alin = 0;
			bool ok = true;
			while (lptr < n) {
				//如果当前非要出站的车而要出战的车已经进站了
				if (!stk.empty() && stk.top() != inp[lptr] && alin >= inp[lptr]) {
					ok = false;
					break;
				}

				while ((stk.empty() || stk.top() != inp[lptr]) && alin < n)stk.push(++alin);
				if (stk.top() == inp[lptr]) {
					stk.pop();
					lptr++;
				}
				else {
					ok = false;
					break;
				}
			}
			if (ok)cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	br1:
		int j = 0;
		
	}

	//while (1);

	return 0;
}