#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr int XN = 200010;
constexpr ll MOD = 1e9 + 7;

int n;
int lim[XN];
int choices[XN];

int solve() {
    vector<int> t;
    for (int i = 0; i < n; i++) {
        int idx = lower_bound(choices, choices + n, lim[i]) - choices;
        if (choices[idx] <= lim[i]) idx++;
        if(idx>=n)return 0;
        t.push_back(n - idx + 1 - 1);
    }
    ll res = t[0];
    for (int i = 1; i < t.size(); i++) {
        if(t[i]-i<=0)return 0;
        res = (res * (t[i] - i)) % MOD;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);

    int kase;
    cin >> kase;
    while (kase--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> choices[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> lim[i];
        }
        sort(lim, lim + n);
        reverse(lim,lim+n);
        sort(choices, choices + n);
        cout << solve() << '\n';
    }
}
