#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int XN = 5010;

int ft[XN];
inline int lowbit(int x) {
    return x&-x;
}
inline void ftadd(int pos, int x) {
    while (pos < XN) {
        ft[pos] += x;
        pos += lowbit(pos);
    }
}
inline ll ftget(int pos) {
    int res = 0;
    while (pos != 0) {
        res += ft[pos];
        pos -= lowbit(pos);
    }
    return res;
}

int n;
int a[XN];
int a_sorted[XN];

int main()
{
    ios::sync_with_stdio(false);

    int kase;
    cin >> kase;
    while (kase--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            a_sorted[i] = a[i];
        }
        sort(a_sorted, a_sorted + n);
        for (int i = 0; i < n; i++)
            a[i] = lower_bound(a_sorted, a_sorted + n, a[i]) - a_sorted+1;
        ll ans = 0;
        for (int l = 0; l < n; l++)
        {
            vector<int> div;
            memset(ft,0,sizeof(ft));
            div.push_back(-1);
            ll res = 0;

            for (int r = l; r < n; r++)
            {
                int kth=ftget(a[r]);
                // cout << "find " << a[r] << " is " << kth << endl;
                while (!div.empty() && *div.rbegin() >= kth)
                {
                    int nxt = *(div.rbegin() + 1) + 1;
                    // cout << "remove " << nxt << " " << *div.rbegin() << endl;
                    res -= *div.rbegin() - nxt;
                    div.erase(div.end() - 1);
                }
                res += (r - l) - (*div.rbegin() + 1);
                div.push_back(r - l);
                ftadd(a[r],1);

                ans += res;

                // cout << l << " " << r << ": ";
                // for (auto x : div)
                // {
                //     cout << x << " ";
                // }
                // cout << "," << res << endl;
            }

            // cout << "-" << endl;
        }
        cout << ans << "\n";
    }

    return 0;
}