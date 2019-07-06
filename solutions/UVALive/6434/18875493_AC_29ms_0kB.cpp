#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int MAXN=150;


int a[MAXN];
int dp[MAXN][MAXN];
int main(){
    int kase;cin>>kase;
    for(int cnt=1;cnt<=kase;cnt++){
        int n,g;cin>>n>>g;
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+1+n);

        memset(dp,0x3f,sizeof(dp));
        dp[0][0]=0;
        for(int k=1;k<=g;k++){
            for(int i=1;i<=n;i++){
                for(int j=0;j<i;j++){
                    dp[i][k]=min(dp[j][k-1]+a[i]-a[j+1],dp[i][k]);
                    //cout<<"group "<<k<<" from "<<j+1<<" to "<<i<<" ="<<dp[i][k]<<endl;
                }
            }
        }
        cout<<"Case #"<<cnt<<": "<<dp[n][g]<<endl;
    }

    return 0;
}

