#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 200010;
typedef long long ll;

ll C[MAXN];
int tn = 0;

int lowbit(int x) {
	return x&-x;
}

ll query(int i) {
	ll res = 0;
	for (; i; i -= lowbit(i)) {
		res = max(res, C[i]);
	}
	return res;
}

void set(int i, ll x) {
	for (; i <= tn; i += lowbit(i)) {
		C[i] = max(x, C[i]);
	}
}

struct Guest {
	int m, y;
	ll d;
	Guest() {
	}
	Guest(int m, int y, ll d) :m(m), y(y), d(d) {
	}
};
map<pair<int, int>, int> sg;
bool cmp_m(const Guest &a, const Guest &b) {
	if (a.m == b.m)return a.y > b.y;
	return a.m < b.m;
}

vector<Guest> gs;
vector<int> appeary;

int main() {
	tn = MAXN - 10;
	int len; cin >> len;
	for (int i = 0; i < len; i++) {
		int m, y, d;
		cin >> m >> y >> d;
		pair<int, int> key = make_pair(m, y);
		if (sg.count(key)) {
			gs[sg[key]].d += d;
		}
		else {
			gs.push_back(Guest(m, y, d));
			sg[key] = (int)gs.size() - 1;
			appeary.push_back(y);
		}
	}
	sort(appeary.begin(), appeary.end());
	for (int i = 0; i < gs.size(); i++) {
		gs[i].y = lower_bound(appeary.begin(), appeary.end(), gs[i].y) - appeary.begin() + 1;
	}
	sort(gs.begin(), gs.end(), cmp_m);
	ll ans = 0;
	for (int i = 0; i < gs.size(); i++) {
		ll tans = query(gs[i].y - 1) + gs[i].d;
		ans = max(ans, tans);
		set(gs[i].y, tans);
	}
	cout << ans << endl;

	//while (1);
	return 0;
}