#include <iostream>
using namespace std;
const int MAXN=10010;
struct UnionTree{
    int fa[MAXN];
    UnionTree(){
        for(int i=0;i<MAXN;i++){
            fa[i]=i;
        }
    }
    int find(int u){
        int uu=u;
        while(fa[uu]!=uu)uu=fa[uu];
        return uu;
    }
    void connect(int u,int v){
        fa[find(u)]=v;
    }
    bool isc(int u,int v){
        return find(u)==find(v);
    }
};
UnionTree ut;
int main(){
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
