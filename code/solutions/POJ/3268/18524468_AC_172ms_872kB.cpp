#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int MAXV=1010,MAXE=100100;
struct Edge{
    int v,n,w;
};
struct Graph{
    Edge edges[MAXE];
    int head[MAXV],idx;
    Graph(){
        idx=0;
    }
    void adde(int u,int v,int w){
        edges[++idx].v=v;
        edges[idx].w=w;
        edges[idx].n=head[u];
        head[u]=idx;
    }
};

Graph g1,g2;

struct v4q{
    int u,dist;
    v4q(){}
    v4q(int u,int dist):u(u),dist(dist){}
    bool operator<(const v4q &b)const{
        return dist>b.dist;
    }
};
int dist[MAXV],dist2[MAXV];
int vis[MAXV];

void dijkstra(Graph &g,int S){
    memset(dist,0x7f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    priority_queue<v4q> pq;
    pq.push(v4q(S,0));
    dist[S]=0;
    while(!pq.empty()){
        int u=pq.top().u;pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int ei=g.head[u];ei;ei=g.edges[ei].n){
            Edge &e=g.edges[ei];
            if(dist[e.v]>dist[u]+e.w){
                dist[e.v]=dist[u]+e.w;
                pq.push(v4q(e.v,dist[e.v]));
            }
        }
    }
}

int main(){
    int vlen,elen,S;
    cin>>vlen>>elen>>S;
    for(int i=0;i<elen;i++){
        int u,v,w;cin>>u>>v>>w;
        g1.adde(v,u,w);
        g2.adde(u,v,w);
    }
    dijkstra(g1,S);
    memcpy(dist2,dist,sizeof(dist));
    dijkstra(g2,S);
    int ans=0;
    for(int i=1;i<=vlen;i++){
        if(i==S)continue;
        ans=max(ans,dist[i]+dist2[i]);
    }
    cout<<ans<<endl;

    return 0;
}
