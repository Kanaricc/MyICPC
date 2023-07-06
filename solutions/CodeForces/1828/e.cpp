#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int XP = 20;
constexpr int XN = 500010;
constexpr ll MOD=1e9+7;

ll qpow(ll a,int b,ll m){
    ll res=1;
    a%=m;
    for(;b;b>>=1,a=(a*a)%m){
        if(b&1)res=(res*a)%m;
    }
    return res;
}

struct SH{
    ll h[XN];
    ll p,m;
    ll pp[XN];
    SH(){
        p=26;
        m=MOD;
        pp[0]=1;
        for(int i=1;i<XN;i++)pp[i]=(pp[i-1]*p)%m;
    }
    void init(const string &str){
        for(int i=0;i<str.size();i++){
            h[i+1]=(h[i]*p+(str[i]-'a'+1))%m;
        }
    }

    ll get(int l,int r){
        ll t=(h[l-1]*pp[r-l+1])%m;
        ll res=((h[r]-t)%m+m)%m;
        return res;
    }
} sp,ss;

int maxlen[XN];
char str[XN],rev[XN];

int f[XN];
vector<int> quit[XN];

int main(){
    ios::sync_with_stdio(false);
    int kase;cin>>kase;
    while(kase--){
        int n;cin>>n;
        for(int i=0;i<n;i++)cin>>str[i];
        for(int i=0;i<n;i++)rev[i]=str[i];
        reverse(rev,rev+n);

        sp.init(str);
        ss.init(rev);
        // cout<<"done"<<endl;
        for(int i=0;i<n;i++)maxlen[i]=0;
        for(int i=0;i<n;i++){
            int l=0,r=i+1+1; // [ )
            while(l+1<r){
                int mid=(l+r)/2;
                int a=i-mid+1,b=i+mid;
                if(a>=0 && b<n && sp.get(a+1,i+1)==ss.get(n-(b+1)+1,n-(i+1)-1+1)){
                    l=mid;
                }else r=mid;
            }
            maxlen[i]=l;
        }

        // cout<<"done"<<endl;
        // for(int i=0;i<n;i++){
        //     cout<<maxlen[i]<<" ";

        // }
        // cout<<endl;

        for(int i=0;i<n;i++)f[i]=0;
        for(int i=0;i<n;i++)quit[i].clear();
        set<int> mid;
        for(int i=0;i<n;i++){
            for(auto x:quit[i])mid.erase(x);
            
            if(!mid.empty()){
                int prev=*mid.rbegin();
                int len=i-prev;
                int prevl=prev-len+1;
                if(prevl-1>=0)f[i]=f[prevl-1];
                f[i]++;
                // cout<<i<<", mid="<<prev<<","<<" from "<<prevl-1<<endl;
            }

            if(maxlen[i]>0){
                int r=i+maxlen[i];
                quit[r+1].push_back(i);
                mid.insert(i);
            }
        }

        ll res=0;
        for(int i=0;i<n;i++)res+=f[i];
        cout<<res<<"\n";
    }

    return 0;
}