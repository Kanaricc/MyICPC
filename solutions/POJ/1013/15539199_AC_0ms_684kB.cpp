#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100;

int real[MAXN];
bool ignore[MAXN];
int main() {
	int kase; cin >> kase;
	while (kase--) {
		memset(real, 0, sizeof(real));
		memset(ignore, 0, sizeof(ignore));
		for (int i = 0; i < 3; i++) {
			string left, right, status;
			cin >> left >> right >> status;


			int offset = 0;
			if (status == "even")offset = 0;
			else if (status == "up")offset = 1;
			else if (status == "down")offset = -1;

			for (int i = 0; i < left.size(); i++) {
				real[left[i] - 'A'] += offset;
				if (offset == 0)ignore[left[i] - 'A'] = 1;
			}
			for (int i = 0; i < right.size(); i++) {
				real[right[i] - 'A'] -= offset;
				if (offset == 0)ignore[right[i] - 'A'] = 1;
			}
		}
		
		char ans;
		int rank = 0;

		for (int i = 0; i <= 30; i++) {
			if (ignore[i] == 1)real[i] = 0;
			if (abs(real[i]) > abs(rank)) {
				rank = real[i];
				ans = i + 'A';
			}
		}

		cout << ans << " is the counterfeit coin and it is " << (rank < 0 ? "light" : "heavy") << ". " << endl;
	}

	return 0;
}