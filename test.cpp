#include <iostream>
#include <vector>
using namespace std;
const int MAXV=100100,MAXE=200100;

struct Edge{
    int v,n;
}edges[MAXE];
int head[MAXV],idx=0;

void adde(int u,int v){
    edges[++idx].v=v;
    edges[idx].n=head[u];
    head[u]=idx;
}
int depth[MAXV];
int maxdepth=0;
void dfs(int u,int dep){
    maxdepth=max(maxdepth,dep);
    depth[u]=dep;
    for(int ei=head[u];ei;ei=edges[ei].n){
        Edge &e=edges[ei];
        dfs(e.v,dep+1);
    }
}
int root;
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        int u;cin>>u;
        if(u==-1)root=i;
        else adde(u,i);
    }

    dfs(root,1);
    cout<<maxdepth<<endl;
    vector<int> ans;
    for(int i=1;i<=n;i++){
        if(depth[i]==maxdepth)ans.push_back(i);
    }
    for(int i=0;i<ans.size()-1;i++){
        cout<<ans[i]<<" ";
    }
    cout<<ans[ans.size()-1]<<endl;

    return 0;
}
        
