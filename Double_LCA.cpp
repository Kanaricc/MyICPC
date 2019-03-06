#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV=50,MAXE=50;
const int MAXP=50;
struct Edge{
    int v,n,w;
}edges[MAXE];
int head[MAXV],idx=0;
int vlen;
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

int lca[MAXV][MAXP],lcaw[MAXV][MAXP];
int depth[MAXV];
int P=0;
void dfs_fa(int u,int fa){
    for(int ei=head[u];ei;ei=edges[ei].n){
        Edge &e=edges[ei];
        if(e.v==fa)continue;
        lca[e.v][0]=u;
        lcaw[e.v][0]=e.w;
        depth[e.v]=depth[u]+1;
        dfs_fa(e.v,u);
    }
}
void init_lca(int root=1){
    for(P=0;(2<<P)<vlen;P++);
    depth[root]=0;
    dfs_fa(root,-1);

    for(int p=1;p<=P;p++){
        for(int u=1;u<=vlen;u++){
            lca[u][p]=lca[lca[u][p-1]][p-1];
        }
    }
    for(int p=1;p<=P;p++){
        for(int u=1;u<=vlen;u++){
            lcaw[u][p]=lcaw[u][p-1]+lcaw[lca[u][p-1]][p-1];
        }
    }
}

struct Query{
    int u,v;
    int res,resw;
    Query(){}
};
vector<Query> queries;
void doquery(int qid){
    int u=queries[qid].u;
    int v=queries[qid].v;
    int &res=queries[qid].res,&resw=queries[qid].resw;

    //approve u is deepper than v
    if(depth[u]<depth[v])swap(u,v);
    //pull u to the same depth of v
    for(int p=P;p>=0;p--){
        if(depth[lca[u][p]]>=depth[v]){
            resw+=lcaw[u][p];
            u=lca[u][p];
        }
    }

    //judge if u is v's child.
    if(u==v){
        res=u;
        return;
    }

    //pull in same time.
    for(int p=P;p>=0;p--){
        if(lca[u][p]!=lca[v][p]){
            resw+=lcaw[u][p]+lcaw[v][p];
            u=lca[u][p];
            v=lca[v][p];
        }
    }

    //add last one.
    resw+=lcaw[u][0]+lcaw[v][0];
    res=lca[u][0];
}

void doqueries(){
    for(int i=0;i<queries.size();i++){
        doquery(i);
    }
}
    
int main(){   
    int elen;cin>>elen;
    for(int i=0;i<elen;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addee(u,v,w);
        vlen=max(vlen,max(u,v));
    }
    int qlen;cin>>qlen;
    for(int i=0;i<qlen;i++){
        Query q;
        cin>>q.u>>q.v;
        queries.push_back(q);
    }
    init_lca(1);
    doqueries();

    for(int i=0;i<qlen;i++){
        cout<<queries[i].res<<" "<<queries[i].resw<<endl;
    }

    return 0;

}
