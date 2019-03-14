#include <iostream>
using namespace std;

double H(int n) {
	double res = 0;
	for (int i = 2; i <= n; i++) {
		res += (1.0 / i);
	}
	return res;
}
const double EPS = 1e-8;
bool cmp(double a, double b) {
	return abs(a - b) <= EPS;
}
int main() {
	ios::sync_with_stdio(false);
	double inp;
	while (cin >> inp) {
		if (cmp(inp, 0.0)) {
			break;
		}
		for (int i = 1; i <= 300; i++) {
			if (H(i) >= inp) {
				cout << i-1 <<" card(s)"<< endl;
				break;
			}
		}
	}

	return 0;
}