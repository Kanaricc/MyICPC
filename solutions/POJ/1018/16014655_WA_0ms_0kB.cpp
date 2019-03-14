#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
const int MAXK = 110;

struct Good {
	int band, price;
} goods[MAXK][110];
int plants[MAXK];
struct A {
	int F, P;
} dp[MAXK];
int main() {
	int kase; cin >> kase;
	while (kase--) {
		int kind = 0;
		 cin >> kind;
		for (int i = 1; i <= kind; i++) {
			int plant; cin >> plant;
			plants[i] = plant;
			for (int j = 1; j <= plant; j++) {
				cin >> goods[i][j].band >> goods[i][j].price;
			}
		}

		dp[0].F = 0x7f7f7f7f;
		dp[0].P = 0;
		for (int i = 1; i <= kind; i++) {
			double factor = 0;
			dp[i] = dp[i - 1];
			if (i - 1 != 0)
				factor = (double)dp[i].F / dp[i].P;
			factor = (double)min(dp[i].F, goods[i][1].band) / (dp[i].P + goods[i][1].price);

			for (int j = 1; j <= plants[i]; j++) {
				if ((double)min(dp[i - 1].F, goods[i][j].band) / (dp[i - 1].P + goods[i][j].price) > factor) {
					dp[i].F = min(dp[i - 1].F, goods[i][j].band);
					dp[i].P = dp[i - 1].P + goods[i][j].price;
					factor = (double)dp[i].F / dp[i].P;
				}
			}
		}

		cout << fixed << setprecision(3) << (double)dp[kind].F / dp[kind].P << endl;
	}
	

	//while (1);
	return 0;
}