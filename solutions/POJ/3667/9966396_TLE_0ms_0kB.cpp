//区间增减
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 100100;
typedef long long LL;
using namespace std;

LL lazy[maxn << 2];
LL sum[maxn << 2];//the number of room
LL le[maxn << 2];
LL re[maxn << 2];
LL maxe[maxn << 2];

void putup(int rt)
{
	if (maxe[rt << 1] == sum[rt << 1]) {
		le[rt] = sum[rt << 1] + le[rt << 1 | 1];
	}
	else {
		le[rt] = le[rt << 1];
	}
	if (maxe[rt << 1 | 1] == sum[rt << 1 | 1]) {
		re[rt] = sum[rt << 1 | 1] + re[rt << 1];
	}
	else {
		re[rt] = re[rt << 1 | 1];
	}
	maxe[rt] = max(max(maxe[rt << 1], maxe[rt << 1 | 1]), re[rt << 1] + le[rt << 1 | 1]);
	//cout << rt << " has been updated with " << maxe[rt] << endl;
}

void putdown(int rt)
{
	//0 is the default value
	if (lazy[rt] == 0)return;
	
	if (lazy[rt] == 1) {
		//when set to full
		lazy[rt << 1] = lazy[rt << 1 | 1] = 1;
		le[rt << 1] = re[rt << 1] = le[rt << 1 | 1] = re[rt << 1 | 1] = 0;
		maxe[rt << 1] = maxe[rt << 1 | 1] = 0;
	}
	else {
		//when set to empty
		lazy[rt << 1] = lazy[rt << 1 | 1] = 2;
		le[rt << 1] = re[rt << 1] = maxe[rt << 1] = sum[rt << 1];
		le[rt << 1 | 1] = re[rt << 1 | 1] = maxe[rt << 1 | 1] = sum[rt << 1 | 1];
	}
	lazy[rt] = 0;
}

void build(int l, int r, int rt)
{
	lazy[rt] = 0;
	re[rt] = le[rt] = maxe[rt] = sum[rt] = r - l + 1;//at the first all rooms are empty
													 //cout<<l<<" to "<<r<<" 's sum="<<sum[rt]<<endl;
	if (l == r) return;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	putup(rt);
}

void update(int L, int R, int c, int l, int r, int rt)
{
	putdown(rt);
	//calculate c
	//L,R
	if (L <= l && r <= R) {
		lazy[rt] = c;
		if (c == 1) {
			re[rt] = le[rt] = maxe[rt] = 0;
			//cout << l << " to " << r << " are set to full" << endl;
		}
		else {
			//cout << l << " to " << r << " are set to empty" << endl;
			re[rt] = le[rt] = maxe[rt] = sum[rt];
		}
		return;
	}

	int m = (l + r) >> 1;
	if (L <= m)
		update(L, R, c, lson);
	if (m < R)
		update(L, R, c, rson);
	putup(rt);
}

LL query(int len, int l, int r, int rt)
{
	putdown(rt);//<-
	if (l == r)return l;

	int m = (l + r) >> 1;
	if (maxe[rt << 1] >= len) {
		//cout << "walk to the left son" << endl;
		return query(len, lson);
	}
	else if (re[rt << 1] + le[rt << 1 | 1] >= len) {
		//cout << "combine two son.the intervel starts at " << m - re[rt << 1] + 1 << endl;
		return m - re[rt << 1] + 1;
	}
	else {
		//cout << "walk to the right son" << endl;5
		return query(len, rson);
	}
}

int main()
{
	int n, m;cin >> n >> m;
	build(1, n, 1);
	while (m--) {
		int op;cin >> op;
		if (op == 1) {
			int len;cin >> len;
			if (maxe[1]<len) {
				cout << 0 << endl;
				continue;
			}
			int pos = query(len, 1, n, 1);
			update(pos, pos + len - 1, 1, 1, n, 1);
			cout << pos << endl;
		}
		else if (op == 2) {
			int pos, len;cin >> pos >> len;
			update(pos, pos + len - 1, 2, 1, n, 1);
		}
	}
	return 0;
}