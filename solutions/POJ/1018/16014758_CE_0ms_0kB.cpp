#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
const int MAXK = 110;

struct Good {
	int band, price;
} goods[MAXK][110];
int plants[MAXK];

int dp[MAXK][5000];
int main() {
	int kase; cin >> kase;
	while (kase--) {
		int kind = 0;
		cin >> kind;

		int maxband = 0;
		for (int i = 1; i <= kind; i++) {
			int plant; cin >> plant;
			plants[i] = plant;
			for (int j = 1; j <= plant; j++) {
				cin >> goods[i][j].band >> goods[i][j].price;
				maxband = max(maxband, goods[i][j].band);
			}
		}

		memset(dp, 0x7f, sizeof(dp));
		for (int k = 1; k <= plants[1]; k++)dp[1][goods[1][k].band] = goods[1][k].price;


		for (int i = 1; i <= kind; i++) {
			for (int j = 0; j <= maxband; j++) {
				for (int k = 1; k <= plants[i]; k++) {
					if (dp[i][min(j, goods[i][k].band)] > dp[i - 1][j] + goods[i][k].price)
						dp[i][min(j, goods[i][k].band)] = dp[i - 1][j] + goods[i][k].price;
				}
			}
		}
		double ans = 0;
		for (int j = 1; j <= maxband; j++) {
			ans = max(ans, (double)j / dp[kind][j]);
		}

		cout << fixed << setprecision(3) << ans << endl;
	}
	

	//while (1);
	return 0;
}