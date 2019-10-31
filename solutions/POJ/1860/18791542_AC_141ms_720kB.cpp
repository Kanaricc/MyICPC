#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int MAXE=1000,MAXV=1000;

struct Edge{
    int v,n;
    double cost,k;
}edges[MAXE];
int head[MAXV],idx=0;
void adde(int u,int v,double cost,double k){
    edges[++idx].v=v;
    edges[idx].cost=cost;
    edges[idx].k=k;
    edges[idx].n=head[u];
    head[u]=idx;
}

struct v4q{
    int u;
    double dist;
    v4q(){}
    v4q(int u,double dist):u(u),dist(dist){}
    bool operator<(const v4q &b)const{
        return dist<b.dist;
    }
};
double dist[MAXV];
int vis[MAXV];
int vlen,elen;
bool dijkstra(int S,double base){
    priority_queue<v4q> pq;
    memset(vis,0,sizeof(vis));
    memset(dist,0,sizeof(dist));
    dist[S]=base;
    pq.push(v4q(S,base));
    while(!pq.empty()){
        int u=pq.top().u;pq.pop();
        vis[u]++;
        //cout<<"arrive "<<u<<" with money "<<dist[u]<<endl;
        if(vis[u]>vlen)return true;
        if(u==S && dist[u]>base)return true;
        for(int ei=head[u];ei;ei=edges[ei].n){
            Edge &e=edges[ei];
            if(dist[e.v]<(dist[u]-e.cost)*e.k){
                dist[e.v]=(dist[u]-e.cost)*e.k;
                pq.push(v4q(e.v,dist[e.v]));
            }
        }
    }
    return dist[S]>base;
}

int main(){
    int kind;
    double base;
    cin>>vlen>>elen>>kind>>base;
    for(int i=0;i<elen;i++){
        int a,b;
        cin>>a>>b;
        double rate,com;
        cin>>rate>>com;
        adde(a,b,com,rate);
        cin>>rate>>com;
        adde(b,a,com,rate);
    }
    cout<<(dijkstra(kind,base)?"YES":"NO")<<endl;

    return 0;
}
