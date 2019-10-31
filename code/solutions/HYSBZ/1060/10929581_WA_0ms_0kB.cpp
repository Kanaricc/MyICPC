#include <iostream>
using namespace std;
const int MAXV=500010,MAXE=500010*2;
struct Edge{
    int v,n,w;
    Edge(){}
};
Edge edges[MAXE];
int head[MAXV],idx=0;
void adde(int u,int v,int w){
    edges[++idx].v=v;
    edges[idx].w=w;
    edges[idx].n=head[u];
    head[u]=idx;
}
int dist[MAXV];//节点到根节点的距离
int mdep[MAXV];//这记录着当前节点到它最深节点的深度
void dfs(int u,int fa){
    for(int ei=head[u];ei;ei=edges[ei].n){
        Edge &e=edges[ei];
        if(e.v==fa)continue;

        dist[e.v]=dist[u]+e.w;
        dfs(e.v,u);
        mdep[u]=max(mdep[u],mdep[e.v]+e.w);
    }
}

int ans=0;
void solve(int u,int fa){
    //查询当前节点到其最深节点的距离
    int tmp=mdep[u];
    for(int ei=head[u];ei;ei=edges[ei].n){
        Edge &e=edges[ei];
        if(e.v==fa)continue;

        //查询这个子节点的最深节点距离
        int curdep=mdep[e.v];
        ans+=tmp-(curdep+e.w);
        solve(e.v,u);
    }
}
int main(){
    int vl,rt;cin>>vl>>rt;
    for(int i=0;i<vl-1;i++){
        int u,v,w;cin>>u>>v>>w;
        adde(u,v,w);adde(v,u,w);
    }
    dfs(rt,0);
    /*
    for(int i=1;i<=vl;i++){
        cout<<i<<"="<<mdep[i]<<endl;
    }
    cout<<"==============="<<endl;
    */

    solve(rt,0);
    cout<<ans<<endl;

    return 0;
}