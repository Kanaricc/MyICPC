#include <iostream>
using namespace std;
const int MAXN = 1010;
int kind, len;
int cou[MAXN];
bool check() {
	for (int i = 2; i <= kind; i++) {
		if (cou[i] != cou[i - 1])return false;
	}
	return true;
}
int main() {
	cin >> kind >> len;
	for (int i = 0; i < len; i++) {
		int x; cin >> x;
		cou[x]++;
	}
	int amin = 0x7f7f7f7f, mini = 0;
	int amax = 0, maxi = 0;
	for (int i = 1; i <= kind; i++) {
		if (cou[i] < amin) {
			amin = cou[i];
			mini = i;
		}
	}
	for (int i = 1; i <= kind; i++) {
		if (cou[i] > amax) {
			amax = cou[i];
			maxi = i;
		}
	}

	//operation1
	{
		//remove
		cou[maxi]--;
		if (check()) {
			cout << "-" << maxi << endl;
			goto ed;
		}
		cou[maxi]++;
	}
	{
		//add
		cou[mini]++;
		if (check()) {
			cout << "+" << mini << endl;
			goto ed;
		}
		cou[mini]--;
	}
	{
		cou[mini]++;
		cou[maxi]--;
		if (check()) {
			cout << "-" << maxi << " +" << mini << endl;
			goto ed;
		}
	}
	cout << "*" << endl;
ed:
	//while (1);
	return 0;
}