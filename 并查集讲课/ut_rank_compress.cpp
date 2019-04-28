#include <iostream>
using namespace std;
const int MAXN=10010;
struct UnionTree{
    int fa[MAXN];
    int w[MAXN];
    UnionTree(){
        for(int i=0;i<MAXN;i++){
            fa[i]=i;
            w[i]=1;
        }
    }
    int find(int u){
        return fa[u]==u?u:fa[u]=find(fa[u]);
    }
    void connect(int u,int v){
        int uf=find(u),vf=find(v);
        int uf=find(u),vf=find(v);
        if(w[uf]<w[vf]){
            fa[uf]=vf;
        }else if(w[uf]>w[vf]{
            fa[vf]=uf;
        }else{
            fa[uf]=vf;
            w[vf]++;
        }
    }
    bool isc(int u,int v){
        return find(u)==find(v);
    }
};
UnionTree ut;
int main(){
    ios::sync_with_stdio(false);
    int n,m;cin>>n>>m;
    int opt,a,b;
    while(cin>>opt){
        cin>>a>>b;
        if(opt==2){
            cout<<(ut.isc(a,b)?"Y":"N")<<endl;
        }else{
            ut.connect(a,b);
        }
    }

    return 0;
}
