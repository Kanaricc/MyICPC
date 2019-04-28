#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
const int MAXV=600,MAXE=30000;

struct Edge{
    int v,n;
}edges[MAXE];
int head[MAXV],idx=0;

void adde(int u,int v){
    edges[++idx].v=v;
    edges[idx].n=head[u];
    head[u]=idx;
}
void adee(int u,int v){
    adde(u,v);
    adde(v,u);
}
int dfn[MAXV],low[MAXV],tick=0;
int root=0;
set<int> res;
void tarjan(int u,int fa,int fe){
    dfn[u]=low[u]=++tick;
    int sum=0;
    for(int ei=head[u];ei;ei=edges[ei].n){
        Edge &e=edges[ei];
        if(!dfn[e.v]){
            tarjan(e.v,u,ei);
            if(low[e.v]<low[u])low[u]=low[e.v];
            if(low[e.v]>=dfn[u])sum++;
        }else if(dfn[e.v]<low[u])low[u]=dfn[e.v];
    }
    if(sum>=2 || (sum==1 && u!=root)){
        res.insert(u);
    }
}


int main(){
    int vlen,elen;
    cin>>vlen>>elen;
    for(int i=0;i<elen;i++){
        int u,v;cin>>u>>v;
        adee(u,v);
    }
    tarjan(0,-1,0);
    int qlen;cin>>qlen;
    while(qlen--){
        int u;cin>>u;
        if(res.count(u)){
            cout<<"Red Alert: City "<<u<<" is lost!"<<endl;
        }else{
            cout<<"City "<<u<<" is lost."<<endl;
        }
    }
    cout<<"Game Over."<<endl;

    return 0;
}

