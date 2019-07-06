#include <iostream>
#include <cstring>
using namespace std;
const int MAXN=1000010;

int a[MAXN];
int dp[MAXN];
int maxj[MAXN];//save max dp[-?][j-1]
int main(){
    ios::sync_with_stdio(false);
    int len,glen;
    int ans=0;
    while(cin>>glen>>len){
        memset(dp,0,sizeof(dp));
        memset(maxj,0,sizeof(maxj));
        for(int i=1;i<=len;i++)cin>>a[i];
        for(int j=1;j<=glen;j++){
            ans=-0x3f3f3f3f;
            for(int i=j;i<=len;i++){
                dp[i]=max(dp[i-1],maxj[i-1])+a[i];
            }
            maxj[j-1]=-0x3f3f3f3f;
            for(int i=j;i<=len;i++){
                maxj[i]=max(maxj[i-1],dp[i]);
                ans=max(ans,dp[i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
} 

