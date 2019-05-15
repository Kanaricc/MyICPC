#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN=10;
const ll P=998244353;
ll C[MAXN][MAXN];
ll qpow(ll a,ll x,ll p){
    ll res=1;
    for(;x;x>>=1,a=(a*a)%p){
        if(x&1)res=(res*a)%p;
    }
    return res;
}
ll getinverse(ll x){
    return qpow(x,P-2,P);
}
void init_c(){
    for(int i=1;i<MAXN;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=((C[i][j-1]*(i-j+1))%P*getinverse(j))%P;
        }
    }
    for(int i=1;i<MAXN;i++){
        for(int j=0;j<=i;j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
}
int dp[MAXN][MAXN];
int main(){
    init_c();
    int kase;cin>>kase;
    while(kase--){
        int nlen,round,sel;
        cin>>nlen>>round>>sel;
        string S,T;
        cin>>S>>T;
        int ji=0;
        for(int i=0;i<nlen;i++)
            if(S[i]==T[i])ji++;

        for(int i=1;i<=round;i++){
            for(int j=0;i<=ji;j++){
                //j odd
                //neln-j even
                for(int k=0;k<=j;k++){
                    dp[i][j]=dp[i][j]+dp[i-1][j-k]*C[nlen-(j-k)][k]*C[j-k][
    }
    return 0;
}

