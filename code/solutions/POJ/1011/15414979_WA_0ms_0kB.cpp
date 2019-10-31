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
bool dfs(int origin,int len, int last,int neednum) {
	//木棍用完但是当前还没拼完
	if (last == 0) {
		if (len == 0)return 1;
		else return 0;
	}
	//你分炸了
	//当前的已经拼完
	if (len == 0) {
		if (origin*(neednum-1) != last)return 0;
		if (dfs(origin, origin, last, neednum - 1)) {
			return 1;
		}
		else return 0;

	}

	for (int i = MAXSINGLELEN - 1; i > 0; i--) {
		if (stick[i] > 0 && len - i >= 0) {
			stick[i]--;
			if (dfs(origin, len - i, last - i, neednum)) {
				return 1;
			}
			if (origin == len)return 0;
			stick[i]++;
		}
	}
	//无法拼上
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
		bool hassolution = false;
		for (int i = minlen; i <= maxlen; i++) {
			if (sticksum%i != 0) {
				//the test stick can't be separeted into single sticks judged by sum
				continue;
			}
			memcpy(stick, originstick, sizeof(originstick));

			if (dfs(i, i, sticksum, sticksum / i)) {
				cout << i << endl;
				hassolution = 1;
				break;
			}
		}
		if (!hassolution) {
			cout << sticksum << endl;
		}

	}

	return 0;
}