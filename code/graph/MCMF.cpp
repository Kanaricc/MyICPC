#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
constexpr int MAXV=5050,MAXE=5500000;

struct Edge{
    int u,v,cap,cost;
    Edge(){}
    Edge(int u,int v,int cap,int cost):u(u),v(v),cap(cap),cost(cost){}
}edges[MAXE];
int idx=0;
vector<int> g[MAXV];
void adde(int u,int v,int cap,int cost){
    //cout<<u<<"->"<<v<<"="<<cap<<","<<cost<<endl;
    g[u].push_back(idx);
    edges[idx++]=Edge(u,v,cap,cost);
    g[v].push_back(idx);
    edges[idx++]=Edge(v,u,0,-cost);
}

int S,T;
int dis[MAXV];
int inq[MAXV],from[MAXV];
int cost=0;
int BFS(){
    fill(from,from+MAXV,-1);
    queue<int> q;
    q.push(S);
    memset(dis,0x3f,sizeof(dis));
    dis[S]=0;

    while(!q.empty()){
        int h=q.front();q.pop();
//        cout<<"arrive "<<h<<endl;

        inq[h]=0;
        for(int ei=0;ei<g[h].size();ei++){
            Edge &e=edges[g[h][ei]];
            if(e.cap>0 && dis[e.v]>dis[h]+e.cost){
                dis[e.v]=dis[h]+e.cost;
                from[e.v]=g[h][ei];
                if(!inq[e.v]){
                    q.push(e.v);
                    inq[e.v]=1;
                }
            }
        }
    }
    if(from[T]==-1)return false;
    int flow=0x3f3f3f3f;

    for(int i=from[T];i!=-1;i=from[edges[i^1].v]){
        flow=min(flow,edges[i].cap);
    }
    for(int i=from[T];i!=-1;i=from[edges[i^1].v]){
        edges[i].cap-=flow;
        edges[i^1].cap+=flow;
    }
    cost+=dis[T]*flow;
    return flow;
    
}

int DINIC(){
    int ans=0;
    cost=0;
    int temp=0;
    while(temp=BFS())ans+=temp;
    
    return ans;
}
constexpr int MAXN=2010;
int num[MAXN];
int main(){
    ios::sync_with_stdio(false);
    int kase;cin>>kase;
    while(kase--){
        int nlen,sel;cin>>nlen>>sel;
        for(int i=1;i<=nlen*2;i++)g[i].clear();
        g[5000].clear();g[5001].clear();g[5002].clear();
        idx=0;

        for(int i=1;i<=nlen;i++){
            cin>>num[i];
            adde(i,nlen+i,1,-num[i]);
        }
        for(int i=1;i<=nlen;i++){
            for(int j=1;j<i;j++){
                if(num[j]<=num[i])adde(nlen+j,i,1,0);
            }
        }
        S=5000;
        adde(5000,5001,sel,0);
        for(int i=1;i<=nlen;i++)adde(5001,i,1,0);
        for(int i=1;i<=nlen;i++)adde(i+nlen,5002,1,0);
        T=5002;
        DINIC();
        cout<<-cost<<endl;
    }

    return 0;
}
