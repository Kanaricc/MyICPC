#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int MAXV=1010;
int game[MAXV][MAXV];
struct v4q{
    int u,dist;
    v4q(){}
    v4q(int u,int dist):u(u),dist(dist){}
    bool operator<(const v4q &b)const{
        return dist<b.dist;
    }
};
int vlen;
int dist[MAXV];
int vis[MAXV];
void dijkstra(int S){
    priority_queue<v4q> pq;
    memset(dist,0,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[S]=0x7f7f7f7f;
    pq.push(v4q(S,0));
    while(!pq.empty()){
        int u=pq.top().u;pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int v=1;v<=vlen;v++){
            if(dist[v]<min(dist[u],game[u][v])){
                dist[v]=min(dist[u],game[u][v]);
                pq.push(v4q(v,dist[v]));
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    int kase,count=0;
    cin>>kase;
    while(kase--){
        count++;
        int elen;
        cin>>vlen>>elen;
        memset(game,0,sizeof(game));
        for(int i=1;i<=elen;i++){
            int u,v,w;cin>>u>>v>>w;
            game[u][v]=game[v][u]=w;
        }
        dijkstra(1);
        cout<<"Scenario #"<<count<<":"<<endl;

        cout<<dist[vlen]<<endl;
        cout<<endl;
    }

    return 0;
}

