#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 120010;

int marble[10];
int sum = 0;
int dp[MAXN];

int main(){
	ios::sync_with_stdio(false);
	int cnt = 0;
	while (1) {
		cnt++;
		for (int i = 1; i <= 6; i++)cin >> marble[i];
		sum = 0;
		for (int i = 1; i <= 6; i++) {
			sum += i*marble[i];
		}
		int mid = sum / 2;

		if (sum == 0) {
			break;
		}

		bool ok = true;
		if (mid * 2 != sum) {
			ok = false;
			goto echo;
		}

		//main task
		//二进制分解
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for (int i = 1; i <= 6; i++) {
			if (marble[i] == 0)continue;

			for (int j = 1; j <= marble[i]; j *= 2) {
				for (int k = mid; k >= 0; k--) {
					if (dp[k] == 0 || k + j*i > mid)continue;
					dp[k + j*i] = 1;
				}
				marble[i] -= j;
			}
			if (marble[i] == 0)continue;
			for (int k = mid; k >= 0; k--) {
				if (dp[k] == 0 || k + i*marble[i] > mid)continue;
				dp[k + i*marble[i]] = 1;
			}

		}
		if (dp[mid] != 1)ok = false;
		


	echo:
		cout << "Collection #" << cnt << ":" << endl;
		cout << (ok ? "Can be divided." : "Can't be divided.") << endl;
		cout << endl;
	}

	

	

	//while (1);
	return 0;
}