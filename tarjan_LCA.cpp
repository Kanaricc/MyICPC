#include <iostream>
#include <vector>
using namespace std;
const int MAXN=50,MAXV=50,MAXE=50;
struct UT{
    int fa[MAXN];
    UT(){
        for(int i=0;i<MAXN;i++)fa[i]=i;
    }
    int find(int u){
        return fa[u]==u?u:fa[u]=find(fa[u]);
    }
    bool isc(int u,int v){
        return find(u)==find(v);
    }
    void con(int u,int v){
        fa[find(u)]=v;
    }
};

struct Edge{
    int v,n;
}edges[MAXE];
int head[MAXV],idx=0;
inline void adde(int u,int v){
    edges[++idx].v=v;
    edges[idx].n=head[u];
    head[u]=idx;
}
inline void addee(int u,int v){
    adde(u,v);
    adde(v,u);
}
int vis[MAXV];
vector<int> query[MAXV];
UT ut;
int a,b;
void tarjan(int now){
    vis[now]=1;
    for(int ei=head[now];ei;ei=edges[ei].n){
        Edge &e=edges[ei];
        if(!vis[e.v]){
        tarjan(e.v);
        ut.con(e.v,now);
        }
    }
    for(int i=0;i<query[now].size();i++){
        if(vis[query[now][i]]){
            cout<<now<<" "<<query[now][i]<<"->"<<ut.find(query[now][i])<<endl;
        }
    }
}
    
int main(){
    int e;cin>>e;
    for(int i=0;i<e;i++){
        int u,v;cin>>u>>v;
        addee(u,v);
    }
    int a,b;cin>>a>>b;
    query[a].push_back(b);
    query[b].push_back(a);
    tarjan(1);

    return 0;
}
