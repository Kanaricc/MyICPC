#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
const int MAXN = 100010;

string game;
bool check(int step,int offset) {
	if (game[offset] == 'P')return false;
	int ptr = offset + step * 1;
	while (ptr != offset) {
		if (game[ptr] == 'P')return false;
		ptr += step;
		ptr %= game.size();
	}
	return true;
}
int gcd(int a, int b) {
	return !b ? a : gcd(b, a%b);
}

bool ok[MAXN];
int main() {
	cin >> game;
	int len = game.size();
	for (int i = 1; i <len; i++) {
		if (len%i != 0)continue;
		for (int k = 0; k < i; k++) {
			if (check(i, k)) {
				ok[i] = 1;
				break;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i < len; i++) {
		if (ok[gcd(i, len)])ans++;
	}
	cout << ans << endl;

	//while (1);
	return 0;
}