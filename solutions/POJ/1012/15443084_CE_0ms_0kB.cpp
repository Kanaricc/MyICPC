#include <iostream>
using namespace std;
const int MAXPEOPLE = 50;


int out[MAXPEOPLE];
int cache[MAXPEOPLE];
int main() {
	int n;
	while (cin >> n) {
		if (n == 0)break;
		if (cache[n]) {
			cout << cache[n] << endl;
			continue;
		}

		memset(out, 0, sizeof(out));
		int k = n + 1;
		out[0] = 0;//边界条件
		//需要注意的是编号从0开始

		for (int i = 1; i <= n; i++) {
			out[i] = (out[i - 1] + k - 1) % (n * 2 - i + 1);//+1-1的问题没啥好说的，每个人都不一样
			if (out[i] <= n-1) {
				//哦嚯
				i = 0; k++;
			}
		}
		cout << k << endl;
		cache[n] = k;
	}

	return 0;
}