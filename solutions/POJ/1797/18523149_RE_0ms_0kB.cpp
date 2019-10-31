#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
const int MAXV=1010,MAXE=20100;
struct Edge{
    int v,w,n;
}edges[MAXE];
int head[MAXV],idx=0;
void adde(int u,int v,int w){
    edges[++idx].v=v;
    edges[idx].w=w;
    edges[idx].n=head[u];
    head[u]=idx;
}
void adee(int u,int v,int w){
    adde(u,v,w);
    adde(v,u,w);
}

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
    memset(dist,0,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[S]=0x7f7f7f7f;
    pq.push(v4q(S,0));
    while(!pq.empty()){
        int u=pq.top().u;pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int ei=head[u];ei;ei=edges[ei].n){
            Edge &e=edges[ei];
            if(dist[e.v]<min(dist[u],e.w)){
                dist[e.v]=min(dist[u],e.w);
                pq.push(v4q(e.v,dist[e.v]));
            }
        }
    }
}
int main(){
    int kase,count=0;
    cin>>kase;
    while(kase--){
        count++;
        idx=0;
        memset(head,0,sizeof(head));
        int vlen,elen;
        cin>>vlen>>elen;
        for(int i=1;i<=elen;i++){
            int u,v,w;cin>>u>>v>>w;
            adee(u,v,w);
        }
        dijkstra(1);
        cout<<"Scenario #"<<count<<endl;
        cout<<dist[vlen]<<endl;
        cout<<endl;
    }

    return 0;
}

