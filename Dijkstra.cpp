#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAXV=50,MAXE=50;
struct Edge{
    int v,n,w;
}edges[MAXE];
int head[MAXV],idx=0;
void adde(int u,int v,int w){
    edges[++idx].v=v;
    edges[idx].n=head[u];
    edges[idx].w=w;
    head[u]=idx;
}
void addee(int u,int v,int w){
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
priority_queue<v4q> pq;
bool vis[MAXV];
int dist[MAXV];
int dijkstra(int S){
    memset(dist,0x7f,sizeof(dist));
    dist[S]=0;
    pq.push(v4q(S,0));
    while(!pq.empty()){
        int cur=pq.top().u;pq.pop();
        if(vis[cur])continue;
        vis[cur]=1;

        for(int ei=head[cur];ei;ei=edges[ei].n){
            Edge &e=edges[ei];
            if(dist[e.v]>dist[cur]+e.w){
                dist[e.v]=dist[cur]+e.w;
                pq.push(v4q(e.v,dist[e.v]));
            }
        }
    }

    return 0;
}

int main(){
    int elen;cin>>elen;
    for(int i=0;i<elen;i++){
        int u,v,w;cin>>u>>v>>w;
        addee(u,v,w);
    }
    int S;cin>>S;
    dijkstra(S);
    while(cin>>S){
        cout<<dist[S]<<endl;
    }

    return 0;
}
