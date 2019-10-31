#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN=20;
int n,m;
char game[MAXN][MAXN];
int column[MAXN];
long long ans=0;
void dfs(int row,int rest){
    if(n-row+1<rest)return;

    if(row>n || rest<=0){
        if(rest<=0){
            ans++;
        }
        return;
    }
    dfs(row+1,rest);
    for(int i=1;i<=n;i++){
        if(game[row][i]=='.')continue;
        if(!column[i]){
            column[i]=1;
            dfs(row+1,rest-1);
            column[i]=0;
        }
    }
}
int main(){
    while(cin>>n>>m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>game[i][j];
            }
        }
        memset(column,0,sizeof(column));

        ans=0;
        dfs(1,m);
        cout<<ans<<endl;
    }
}
