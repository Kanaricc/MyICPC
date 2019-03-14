#include <iostream>
#include <string>
using namespace std;
const int MAXN=110;
int n,m;
string game[MAXN];
int color[MAXN][MAXN];
void dfs(int x,int y){
    if(x<0 || x>=n || y<0 || y>=m)return;
    if(game[x][y]!='@')return;
    game[x][y]='*';

    const int off[][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,1},{-1,-1},{1,1},{1,-1}};
    for(int i=0;i<8;i++){
        dfs(x+off[i][0],y+off[i][1]);
    }
}
int main(){
    while(cin>>n>>m){
        if(n==0)break;
        for(int i=0;i<n;i++){
                cin>>game[i];
        }
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(game[i][j]=='@'){
                    dfs(i,j);
                    ans++;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
