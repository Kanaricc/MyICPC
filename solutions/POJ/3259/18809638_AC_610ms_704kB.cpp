#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int MAXE=10000,MAXV=1000;

struct Edge{
    int v,n;
    int w;
}edges[MAXE];
int head[MAXV],idx=0;
void adde(int u,int v,int w){
    edges[++idx].v=v;
    edges[idx].w=w;
    edges[idx].n=head[u];
    head[u]=idx;
}
int dist[MAXV];
bool inq[MAXV];
int cnt[MAXV];
int vlen,nelen,pelen;
bool spfa(int S){
    queue<int> pq;
    memset(inq,0,sizeof(inq));
    memset(dist,0x3f,sizeof(dist));
    memset(cnt,0,sizeof(cnt));
    dist[S]=0;
    pq.push(S);
    while(!pq.empty()){
        int u=pq.front();pq.pop();
        inq[u]=false;
        cnt[u]++;
        if(cnt[u]>vlen)return true;
        for(int ei=head[u];ei;ei=edges[ei].n){
            Edge &e=edges[ei];
            if(dist[e.v]>dist[u]+e.w){
                dist[e.v]=dist[u]+e.w;
                if(!inq[e.v]){
                    pq.push(e.v);
                    inq[e.v]=1;
                }
            }
        }
    }
    return false;
}
int main(){
    int kase;cin>>kase;
    while(kase--){
        memset(head,0,sizeof(head));
        idx=0;
        cin>>vlen>>nelen>>pelen;
        for(int i=0;i<nelen;i++){
            int u,v,w;cin>>u>>v>>w;
            adde(u,v,w);
            adde(v,u,w);
        }
        for(int i=0;i<pelen;i++){
            int u,v,w;cin>>u>>v>>w;
            adde(u,v,-w);
        }
        cout<<(spfa(1)?"YES":"NO")<<endl;
    }

    return 0;
}
