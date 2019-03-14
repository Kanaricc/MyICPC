#include <iostream>
#include <algorithm>
using namespace std;

int omarble[10];
int marble[10];
int prefix[10];
int sum = 0;

bool dfs(int curmb, int last) {
	if (last == 0)return true;
	if (curmb < 1)return false;
	if (prefix[curmb] < last)return false;

	int maxx = last / curmb;
	maxx = min(maxx, marble[curmb]);
	for (int i = maxx; i >= 0; i--) {
		if (dfs(curmb -1, last - i*curmb)) {
			return true;
		}
	}

	return false;
}
int main(){
	ios::sync_with_stdio(false);
	int cnt = 0;
	while (1) {
		cnt++;
		for (int i = 1; i <= 6; i++)cin >> marble[i];
		sum = 0;
		for (int i = 1; i <= 6; i++) {
			prefix[i] = prefix[i - 1] + i*marble[i];
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

		if (!dfs(6, mid)) {
			ok = false;
		}



	echo:
		cout << "Collection #" << cnt << ":" << endl;
		cout << (ok ? "Can be divided." : "Can't be divided.") << endl;
		cout << endl;
	}

	

	


	return 0;
}