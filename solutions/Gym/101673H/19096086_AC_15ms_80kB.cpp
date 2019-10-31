#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
const int MAXN=120;
char game[MAXN][MAXN];

int vis[MAXN][MAXN];

queue<pii> q;
int height,width;
void bfs(int x,int y){
    q.push(make_pair(x,y));

    while(!q.empty()){
        pii cur=q.front();q.pop();
        if(vis[cur.first][cur.second])continue;
        vis[cur.first][cur.second]=1;
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                int ox=cur.first+i,oy=cur.second+j;
                if(i==0 && j==0)continue;
                if(ox<=0 || ox>height)continue;
                if(oy<=0 || oy>width)continue;
                if(!vis[ox][oy] && game[ox][oy]=='#')q.push(make_pair(ox,oy));
            }
        }
    }
}

int main(){
    cin>>height>>width;
    for(int i=1;i<=height;i++){
        for(int j=1;j<=width;j++){
            cin>>game[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=height;i++){
        for(int j=1;j<=width;j++){
            if(game[i][j]=='#' && !vis[i][j]){
                ans++;
                bfs(i,j);
            }
        }
    }

    cout<<ans<<endl;

    return 0;
} 
