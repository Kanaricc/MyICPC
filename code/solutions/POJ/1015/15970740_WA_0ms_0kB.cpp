#include <iostream>
#include <algorithm>
#include <stack>
#include <cstring>
#define mmax(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
const int MAXPE = 250;
const int MAXCL = 30,MAXSUB=10000;

int rtcl, cl;
int com[MAXPE][2];
int sum[MAXPE], sub[MAXPE];
int dp[MAXCL][MAXSUB],path[MAXCL][MAXSUB];
int offset = 0;
int main() {
	int kase = 0;
	while (cin >> rtcl >> cl) {
		kase++;
		if (rtcl + cl == 0)break;

		for (int i = 1; i <= rtcl; i++) {
			cin >> com[i][0] >> com[i][1];
			sum[i] = com[i][0] + com[i][1];
			sub[i] = com[i][0] - com[i][1];
			
		}
		memset(dp, -1, sizeof(dp));
		offset = 20 * cl;//we will candidate {cl} at most,everyone's sub is 20 max, then mul it.
		dp[0][offset] = 0;
		
		for (int i = 1; i <= rtcl; i++) {
			for (int j = cl; j > 0; j--) {
				for (int k = sub[i]; k <= offset * 2; k++) {
					if (k < 0 || k - sub[i]>2 * offset)continue;
					if (dp[j - 1][k - sub[i]] == -1)continue;
					
					if (dp[j][k] < dp[j - 1][k - sub[i]] + sum[i]) {
						dp[j][k] = dp[j - 1][k - sub[i]] + sum[i];
						path[j][k] = i;
					}
					
				}
			}
		}

		//寻找最小差
		int tmp = 0;
		while (dp[cl][offset - tmp] + dp[cl][offset + tmp] == -2)tmp++;
		tmp = dp[cl][offset - tmp] > dp[cl][offset + tmp] ? offset - tmp : offset + tmp;
		int original_A = (dp[cl][tmp] + tmp - offset) / 2, original_B = (dp[cl][tmp] - tmp + offset) / 2;

		cout << "Jury #" << kase << endl;
		cout << "Best jury has value "<<original_A<<" for prosecution and value "<<original_B<<" for defence:" << endl;

		//read path

		int cur = tmp;
		stack<int> sk;
		for (int i = cl; i > 0; i--) {
			sk.push(path[i][cur]);
			cur = cur - sub[path[i][cur]];
		}
		while (!sk.empty()) {
			cout << " " << sk.top();
			sk.pop();
		}
		cout << endl << endl;

	}

	return 0;
}