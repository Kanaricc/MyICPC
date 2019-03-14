#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
const int MAX_STAMP = 60;

int stamp[MAX_STAMP];
int stampkind;
struct Solution {
	int ans[MAX_STAMP];
	int kind;
	int sum;
	Solution() {}
};
vector<Solution> solutions;

Solution cursolution;
Solution bestsol;
bool havesol = false;

int compare(const Solution &a, const Solution &b) {
	if (a.kind != b.kind)return a.kind > b.kind ? 1 : 2;
	if (a.sum != b.sum)return a.sum < b.sum ? 1 : 2;

	int maxxa = 0, maxxb = 0;
	for (int i = stampkind - 1; i >= 0; i--) {
		if (a.ans[i] != 0) {
			maxxa = stamp[i]; break;
		}
	}
	for (int i = stampkind - 1; i >= 0; i--) {
		if (b.ans[i] != 0) {
			maxxb = stamp[i]; break;
		}
	}
	if (maxxa != maxxb)
		return maxxa > maxxb ? 1 : 2;
	else return 0;
	
}
int tiee = false;
int collect(int sum, int used, int prenum) {
	if (prenum > 4)return false;
	if (sum == 0) {
		cursolution.kind = 0;
		cursolution.sum = prenum;
		for (int i = 0; i < stampkind; i++) {
			if (cursolution.ans[i] != 0)cursolution.kind++;
		}
		switch (compare(cursolution,bestsol))
		{
		case 1:
			bestsol = cursolution;
			tiee = false;
			break;
		case 2:
			break;
		case 0:
			tiee = 1;
			break;
		}

		havesol = 1;
		return true;
	}
	if (used >= stampkind)return false;

	for (int i = 0;; i++) {
		int rest = sum - i*stamp[used];
		if (rest < 0)break;
		cursolution.ans[used] = i;
		collect(rest, used + 1, prenum + i);
	}
	cursolution.ans[used] = 0;

	return false;
}
int main() {
	while (cin >> stamp[stampkind]) {
		if (stamp[stampkind] != 0) {
			stampkind++;
			continue;
		}
		sort(stamp, stamp + stampkind);

		int customer;
		while (cin >> customer) {
			if (customer == 0)break;
			bestsol.kind = -1;
			havesol = false;

			collect(customer, 0, 0);

			if (!havesol) {
				cout << customer << " ---- none" << endl;
				continue;
			}

			if (!tiee) {
				cout << customer << " (" << bestsol.kind << "):";
				for (int i = 0; i < stampkind; i++) {
					for (int j = 0; j < bestsol.ans[i]; j++) {
						cout << " " << stamp[i];
					}
				}
				cout << endl;
			}
			else {
				cout << customer << " (" << bestsol.kind << "): tie" << endl;
			}
		}

		stampkind = 0;
	}

	return 0;
}