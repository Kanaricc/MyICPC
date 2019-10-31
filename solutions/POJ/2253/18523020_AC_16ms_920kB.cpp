#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
const int MAXV=210;
struct Pos{
    int x,y;
} poses[MAXV];
int game[MAXV][MAXV];

struct v4q{
    int u,dist;
    v4q(){}
    v4q(int u,int dist):u(u),dist(dist){}
    bool operator<(const v4q &b)const{
        return dist>b.dist;
    }
};
int vlen;
int dist[MAXV];
int vis[MAXV];
void dijkstra(int S){
    priority_queue<v4q> pq;
    memset(dist,0x7f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[S]=0;
    pq.push(v4q(S,0));
    while(!pq.empty()){
        int u=pq.top().u;pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int v=1;v<=vlen;v++){
            if(u==v)continue;
            if(dist[v]>max(game[u][v],dist[u])){
                dist[v]=max(dist[u],game[u][v]);
                pq.push(v4q(v,dist[v]));
            }
        }
    }
}
int main(){
    int kase=0;
    while(cin>>vlen){
        kase++;
        if(vlen==0)break;

        for(int i=1;i<=vlen;i++){
            cin>>poses[i].x>>poses[i].y;
        }
        for(int i=1;i<=vlen;i++){
            for(int j=1;j<=vlen;j++){
                game[i][j]=(poses[i].x-poses[j].x)*(poses[i].x-poses[j].x)+(poses[i].y-poses[j].y)*(poses[i].y-poses[j].y);
            }
        }
        dijkstra(1);
        cout<<"Scenario #"<<kase<<endl;
        cout<<fixed<<setprecision(3)<<"Frog Distance = "<<sqrt(dist[2])<<endl;
        cout<<endl;
    }

    return 0;
}

