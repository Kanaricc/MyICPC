#include <iostream>
#include <vector>
using namespace std;

inline int gcd(int a, int b) {
	return !b ? a : gcd(b, a%b);
}
inline int lcm(int a, int b) {
	return a / gcd(a, b)*b;
}
int solve(vector<int> &a, vector<int> &p) {
	int cur = 0, curp = 1;
	for (int i = 0; i < a.size(); i++) {
		int other = a[i], otherp = p[i];
		if (curp < otherp) {
			swap(other, cur);
			swap(curp, otherp);
		}

		while (cur%otherp != other)
			cur += curp;
		curp = lcm(curp, otherp);
	}
	return cur;
}

int main() {
	ios::sync_with_stdio(false);

	vector<int> a, p;
	p.push_back(23);
	p.push_back(28);
	p.push_back(33);
	int a1, a2, a3,d;
	int tnt = 0;
	while (cin >> a1 >> a2 >> a3 >> d) {
		tnt++;
		if (a1 == 0 && a2 == 0 && a3 == 0) {
			cout << "Case " << tnt << ": the next triple peak occurs in " << 21252 - d << " days." << endl;
			continue;
		}
		if (a1 == -1)break;
		a.clear();
		a.push_back(a1 % 23);
		a.push_back(a2 % 28);
		a.push_back(a3 % 33);
		cout << "Case " << tnt << ": the next triple peak occurs in " << solve(a, p) - d << " days." << endl;
	}
	

	//while (1);
	return 0;
}