#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int MAXV=100010;
constexpr int MAXP=20;

vector<int> g[MAXV];
vector<int> rev_g[MAXV];
int ind[MAXV];
void adde(int u,int v){
    g[u].push_back(v);
    rev_g[v].push_back(u);
    ind[v]++;
}

vector<int> topo_res;
int vlen,elen;
constexpr int SUPERS=100005;
void topo_sort(int u){
    queue<int> q;
    for(int u=1;u<=vlen;u++){
        if(!ind[u]){
            q.push(u);
            //mogician
            adde(SUPERS,u);
        }
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        topo_res.push_back(u);
        for(auto v: g[u]){
            ind[v]--;
            if(!ind[v])q.push(v);
        }
    }
}

int lca[MAXV][MAXP];
int depth[MAXV];
void lca_increse(int u,int fa){
    lca[u][0]=fa;
    depth[u]=depth[fa]+1;
    for(int p=1;p<MAXP;p++){
        lca[u][p]=lca[lca[u][p-1]][p-1];
    }
}

int get_lca(int u,int v){
    if(depth[u]<depth[v])swap(u,v);
    for(int p=MAXP-1;p>=0;p--)if(depth[lca[u][p]]>=depth[v])u=lca[u][p];
    if(u==v)return u;
    for(int p=MAXP-1;p>=0;p--)if(lca[u][p]!=lca[v][p])u=lca[u][p],v=lca[v][p];
    return lca[u][0];
}


bool added[MAXV];
int main(){
    ios::sync_with_stdio(false);
    int kase;cin>>kase;
    while(kase--){
        cin>>vlen>>elen;
        for(int i=1;i<=vlen;i++)g[i].clear(),rev_g[i].clear();
        for(int i=0;i<=vlen;i++)for(int p=0;p<MAXP;p++)lca[i][p]=0;
        memset(added,0,sizeof(added));
        topo_res.clear();
        memset(ind,0,sizeof(ind));

        for(int i=0;i<elen;i++){
            int u,v;cin>>u>>v;
            adde(v,u);
        }
        topo_sort(SUPERS);
        //for(auto u:topo_res)cout<<u<<" ";
        //cout<<endl;

        added[SUPERS]=1;
        for(int i=0;i<topo_res.size();i++){
            //find common lca
            int clca=0;
            int u=topo_res[i];
            for(auto v:rev_g[u]){
                if(!added[v])continue;
                if(clca==0)clca=v;
                else clca=get_lca(clca,v);
                //cout<<"merge "<<v<<" = "<<clca<<endl;
            }
            lca_increse(u,clca);
            //cout<<clca<<"->"<<u<<endl;
            added[u]=1;
        }
        int qlen;cin>>qlen;
        while(qlen--){
            int u1,u2;cin>>u1>>u2;
            int l=get_lca(u1,u2);
            cout<<depth[u1]+depth[u2]-depth[l]<<endl;
        }
    }

    return 0;
}
