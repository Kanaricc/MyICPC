#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;
const int MAX_STAMP = 50;

int stamp[MAX_STAMP];
int stampkind;
struct Solution {
	int ans[MAX_STAMP];
	int kind;
	int sum;
	Solution() {}
	bool operator < (const Solution &b)const {
		if (kind != b.kind)return kind > b.kind;
		if (sum != b.sum)return sum < b.sum;

		int maxxa = 0, maxxb = 0;
		for (int i = stampkind - 1; i >= 0; i--) {
			if (ans[i] != 0) {
				maxxa = stamp[i]; break;
			}
		}
		for (int i = stampkind - 1; i >= 0; i--) {
			if (b.ans[i] != 0) {
				maxxb = stamp[i]; break;
			}
		}
		return maxxa > maxxb;
	}
};
vector<Solution> solutions;

Solution cursolution;
int collect(int sum, int used,int prenum) {
	if (prenum > 4)return false;
	if (sum == 0) {
		cursolution.kind = 0;
		cursolution.sum = prenum;
		for (int i = 0; i < stampkind; i++) {
			if (cursolution.ans[i] != 0)cursolution.kind++;
		}

		solutions.push_back(cursolution);
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

			solutions.clear();

			collect(customer, 0, 0);

			if (solutions.size() == 0) {
				cout << customer << " ---- none" << endl;
				continue;
			}

			sort(solutions.begin(), solutions.end());

			bool tied = false;
			if (solutions.size() > 1
				&& solutions[0].kind == solutions[1].kind
				&& solutions[0].sum == solutions[1].sum) {
				Solution &sa = solutions[0];
				Solution &sb = solutions[1];

				int maxxa = 0, maxxb = 0;
				for (int i = stampkind - 1; i >= 0; i--) {
					if (sa.ans[i] != 0) {
						maxxa = stamp[i]; break;
					}
				}
				for (int i = stampkind - 1; i >= 0; i--) {
					if (sb.ans[i] != 0) {
						maxxb = stamp[i]; break;
					}
				}
				if (maxxa == maxxb)tied = 1;
			}

			if (!tied) {
				cout << customer << " (" << solutions[0].kind << "): ";
				for (int i = 0; i < stampkind; i++) {
					for (int j = 0; j < solutions[0].ans[i]; j++) {
						cout << stamp[i] << " ";
					}
				}
				cout << endl;
			}
			else {
				cout << customer << " (" << solutions[0].kind << "): tie" << endl;
			}
		}

		stampkind = 0;
	}
	//sort(stamp, stamp + stampkind, greater<int>());

	

	//while (1);
	return 0;
}