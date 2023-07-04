#include <algorithm>
#include <cstring>
#include <stack>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int XN = 300010;
constexpr int XP=20;

int n;
int a[XN],a_sorted[XN];
int l[XN],r[XN];
int maxx[XN][XP];

int main(){
    ios::sync_with_stdio(false);

    int kase;
    cin >> kase;
    while (kase--){
        cin >> n;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            a_sorted[i] = a[i];
        }
        sort(a_sorted, a_sorted + n);
        for (int i = 0; i < n; i++)
            a[i] = lower_bound(a_sorted, a_sorted + n, a[i]) - a_sorted;
        
        stack<int> q;
        for(int i=0;i<n;i++){
            while(!q.empty() && a[q.top()]>a[i])q.pop();
            if(q.empty())l[i]=-1;
            else l[i]=q.top();
            q.push(i);
        }
        while(!q.empty())q.pop();
        for(int i=n-1;i>=0;i--){
            while(!q.empty() && a[q.top()]>a[i])q.pop();
            if(q.empty())r[i]=n;
            else r[i]=q.top();
            q.push(i);
        }
        // for(int i=0;i<n;i++){
        //     cout<<l[i]<<" ";
        // }
        // cout<<endl;
        // for(int i=0;i<n;i++){
        //     cout<<r[i]<<" ";
        // }
        // cout<<endl;

        for(int i=0;i<n;i++)maxx[i][0]=a[i];
        for(int p=1;p<XP;p++){
            for(int i=1<<(p-1);i<n;i++){
                maxx[i][p]=max(maxx[i][p-1],maxx[i-(1<<(p-1))][p-1]);
            }
        }

        ll ans = 0;
        for(int i=1;i<=n;i++)ans+=(ll)i*(i-1)/2;
        for (int i = 0; i < n; i++){
            int t=l[i];
            for(int p=XP-1;p>=0;p--){
                if(t+1>=(1<<p) && maxx[t][p]<a[i])
                    t-=1<<p;
            }
            // cout<<i<<" "<<t<<" "<<l[i]<<" "<<r[i]<<endl;
            ans-=(ll)(r[i]-i)*(l[i]-t);
        }
        cout<<ans<<endl;
    }

    return 0;
}