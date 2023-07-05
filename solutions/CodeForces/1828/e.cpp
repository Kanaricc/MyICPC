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
constexpr int XN = 300010;
constexpr ll MOD=19260817;

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
    void init(const string &str){
        p=26;
        m=MOD;
        for(int i=0;i<str.size();i++){
            h[i+1]=(h[i]*p+(str[i]-'a'+1))%m;
        }
    }

    ll get(int l,int r){
        ll t=(h[l-1]*qpow(p,r-l+1,m))%m;
        ll res=((h[r]-t)%m+m)%m;
        return res;
    }
} sp,ss;

int maxlen[XN];
char str[XN],rev[XN];


int d1[XN],dopen[XN],dtag[XN];
int lc[XN],rc[XN],idx=0,root=0;
void build(int l,int r,int n){
    n=++idx;
    if(l>=r){
        d1[n]=0;dtag[n]=1;
    }
    int mid=(l+r)/2;
    build(l,mid,lc[n]);
    build(mid+1,r,rc[n]);
    d1[n]=dtag[n]=1;
}
void push_down(int n){
    if(dtag[n]!=1){
        dtag[lc[n]]=dtag[n];
        dtag[rc[n]]=dtag[n];
        dtag[n]=1;
    }
}
void push_up(int n){
    d1[n]=d1[lc[n]]*dtag[lc[n]]+d1[rc[n]]*dtag[rc[n]];
}
void modify_value(int pos,int x,int L,int R,int n){
    if(L==pos && pos==R){
        d1[n]=x;
        return;
    }
    push_down(n);
    int mid=(L+R)/2;
    if(x<=mid)modify_value(pos,x,L,mid,lc[n]);
    else modify_value(pos,x,mid+1,R,rc[n]);
    push_up(n);
}
void modify_times(int )

int f[XN],prefix[XN];

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
        for(int i=0;i<n;i++){
            for(int p=XP;p>=0;p--){
                int l=i-(maxlen[i]+(1<<p))+1;
                int r=i+(maxlen[i]+(1<<p));
                if(l>=0 && r<n){
                    cout<<"at "<<i<<" check "<<l<<" "<<r<<": ";
                    for(int j=l;j<=i;j++)cout<<str[j];
                    cout<<",";
                    for(int j=n-(r+1);j<=n-(i+1)-1;j++)cout<<rev[j];
                    cout<<endl;
                    // sp and ss start from position 1
                    cout<<sp.get(l+1,i+1)<<" "<<ss.get(n-(r+1)+1,n-(i+1)-1+1)<<endl;
                    if(sp.get(l+1,i+1)==ss.get(n-(r+1)+1,n-(i+1)-1+1)){
                        maxlen[i]+=1<<p;
                    }
                }
            }
        }
        for(int i=0;i<n;i++){
            cout<<maxlen[i]<<" ";
        }
        cout<<endl;


        



    }
}