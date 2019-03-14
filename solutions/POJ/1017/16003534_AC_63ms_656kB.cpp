#include <iostream>
#include <algorithm>
using namespace std;

int inp[10];
int main() {
	while (1) {
		for (int i = 1; i <= 6; i++)cin >> inp[i];

		int sum = 0;
		for (int i = 1; i <= 6; i++)sum += inp[i];
		if (sum == 0)break;

		int ans = 0;
		//for 6x6
		ans += inp[6];
		//for 5x5
		{
			ans += inp[5];
			int tmp = inp[5] * (6 * 6 - 5 * 5);
			inp[1] -= tmp;
			inp[1] = max(0, inp[1]);
		}
		//for 4x4
		{
			ans += inp[4];
			int tmp = inp[4] * (6 * 6 - 4 * 4);
			int x2 = tmp / 4;
			if (x2 > inp[2]) {
				tmp -= inp[2] * 4;
				inp[2] = 0;
				inp[1] -= tmp;
				inp[1] = max(0, inp[1]);
			}
			else {
				//x2<inp[2];
				inp[2] -= x2;
			}

			//for 3x3
			{
				int tmp = inp[3] / 4;
				int rest = inp[3] % 4;
				ans += tmp;
				if (rest) {
					ans++;
					int tmp2 = 6 * 6 - rest * 3 * 3;
					//1->5 2->3 3->1
					inp[2] -= 7 - 2 * rest;
					tmp2 -= (7 - 2 * rest) * 2 * 2;
					inp[1] -= tmp2;
				}
			}
			//for 2x2
			{
				inp[2] = max(0, inp[2]);
				int tmp = inp[2] / 9;
				int rest = inp[2] % 9;

				ans += tmp;
				if (rest) {
					ans++;
					int tmp2 = 6 * 6 - rest * 2 * 2;
					inp[1] -= tmp2;
				}
			}
			//for 1x1
			{
				inp[1] = max(0, inp[1]);
				int tmp = inp[1] / 36;
				int rest = inp[1] % 36;
				ans += tmp;
				if (rest)ans++;
			}

			cout << ans << endl;
		}
		
	}

	return 0;
}