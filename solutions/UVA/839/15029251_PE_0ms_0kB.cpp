#include <iostream>
using namespace std;

int build() {
	int lw, ld, rw, rd;
	cin >> lw >> ld >> rw >> rd;
	if (lw == 0) {
		lw = build();
	}
	if (rw == 0) {
		rw = build();
	}
	if (rw*lw < 0)return -1;
	if (lw*ld == rw*rd)return lw + rw;
	else return -1;
}
int main() {
	int kase;
	cin >> kase;
	while (kase--) {
		if (build() > 0)cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}