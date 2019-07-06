#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 10;

int pp[MAXN], ord[MAXN];
int main() {
	for (int i = 0; i < 3; i++)cin >> pp[i];
	for (int i = 0; i < 3; i++)cin >> ord[i];
	int ans = 0;
	for (int j = 0; j < 3; j++) {
		ans += max(0, ord[j] - pp[j]);
	}
	cout << ans << endl;

	//while (1);
	return 0;
}