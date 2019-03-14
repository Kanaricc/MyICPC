#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double sum = 0;
	for (int i = 0; i < 12; i++) {
		double inp; cin >> inp;
		sum += inp;
	}
	cout << fixed << setprecision(2) << "$" << sum / 12.0 << endl;

	//while (1);
	return 0;
}