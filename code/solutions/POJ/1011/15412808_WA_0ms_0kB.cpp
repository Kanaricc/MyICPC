#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXSINGLELEN = 60;

int n;
int stick[MAXSINGLELEN];
int originstick[MAXSINGLELEN];

/*
something need to cautious.
if a stick could be recycle, it's won't influent the other stick.
*/
bool dfs(int len) {
	if (len == 0)return 1;

	for (int i = MAXSINGLELEN - 1; i > 0; i--) {
		if (stick[i] > 0 && len-i>=0) {
			stick[i]--;
			if (dfs(len - i)) {
				return 1;
			}
			stick[i]++;
		}
	}

	return 0;//false
}
inline bool stickempty() {
	for (int i = MAXSINGLELEN; i > 0; i--) {
		if (stick[i] > 0)return false;
	}
	return true;
}
int main() {
	ios::sync_with_stdio(false);
	while (cin >> n) {
		if (n == 0)break;
		memset(originstick, 0, sizeof(originstick));

		int minlen = 0x7f7f7f7f, sticksum = 0;
		for (int i = 0; i < n; i++) {
			int inp; cin >> inp;
			originstick[inp]++;
			minlen = min(inp, minlen);
			sticksum += inp;
		}
		int maxlen = sticksum / 2;
		for (int i = minlen; i <= maxlen; i++) {
			if (sticksum%i != 0) {
				//the test stick can't be separeted into single sticks judged by sum
				continue;
			}
			memcpy(stick, originstick, sizeof(originstick));

			bool ok = true;
			while (!stickempty()) {
				if (!dfs(i)) {
					ok = false;
					break;
				}
			}

			if (ok) {
				cout << i << endl;
				break;
			}
		}


	}

	return 0;
}