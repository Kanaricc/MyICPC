/*************************************************************************
    > File Name: 5784.cpp
    > Author: jiangyuzhu
    > Mail: 834138558@qq.com 
    > Created Time: 2016/10/4 14:28:41
 ************************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 5;
struct P{
    ll x, y;
    P() {}
    P(ll x, ll y) : x(x), y(y){}
    P operator + (P p){
        return P(x + p.x, y + p.y);
    }
    P operator -(P p){
        return P(x -p.x, y - p.y);
    }
    ll dot(P p){
        return x * p.x +  y *p.y;
    }
    ll det(P p){
        return x * p.y - y * p.x;
    }
	bool operator < (const P& a) const{
		if(y * a.y <= 0){
			if(y > 0 || a.y > 0) return y < a.y;
			if(y == 0 && a.y == 0) return x < a.x;
		}
		return x * a.y - y * a.x > 0;
	}
}p[maxn], q[maxn << 1];
int main (void)
{
	int n;
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; ++i){
			scanf("%lld%lld", &p[i].x, &p[i].y);
		}
		ll line = 0;
		ll ans = n * 1ll * (n - 1) * (n - 2) / 6;
		for(int i = 0; i < n; ++i){
			int tot = 0;
			for(int j = 0; j < n; ++j){
				if(i == j) continue;
				q[tot++] = p[j] - p[i];
			}
			int tmp = 0;
			sort(q, q + tot);
			for(int j = 0; j < tot; ++j) q[tot + j] = q[j];
			for(int j = 0; j < tot - 1; ++j){
				if(q[j].det(q[j + 1]) == 0 && q[j].dot(q[j + 1]) > 0) tmp++;//三点共线
				else tmp = 0;
				line += tmp;
			}
			int cnt1 = 0, cnt2 = 0;
			for(int j = 0; j < tot; ++j){
				while(cnt1 <= j || (cnt1 - tot < j && q[cnt1].det(q[j]) < 0 && q[j].dot(q[cnt1]) > 0)) cnt1++;//左边锐角个数
				while(cnt2 <= j || (cnt2 - tot < j && q[cnt2].det(q[j]) < 0)) cnt2++;//左边角个数
				ans -= cnt2 - cnt1;
			}
		}
		ans -= line / 2;
		printf("%lld\n", ans);
	}
	return 0;
}
