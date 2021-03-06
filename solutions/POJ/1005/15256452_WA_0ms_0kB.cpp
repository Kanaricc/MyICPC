#include <iostream>
#include <cmath>
using namespace std;

const double PI = acos(double(-1));

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double x, y; cin >> x >> y;
		double square = PI*(x*x + y*y);
		square /= 2.0;
		double kth = square / 50;
		int ans = kth;
		if (kth > ans)ans++;
		cout << ans << endl;
	}

	return 0;
}