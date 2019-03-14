#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=1010;
struct UK{
    int fa[MAXN];
    UK(){
        for(int i=0;i<MAXN;i++){
            fa[i]=i;
        }
    }
    int find(int u){
        return fa[u]==u?u:fa[u]=find(fa[u]);
    }
    bool isc(int u,int v){
        return find(u)==find(v);
    }
    void con(int u,int v){
        int ufa=find(u),vfa=find(v);
        if(ufa==vfa)return;
        fa[ufa]=vfa;
    }
};
inline int getdist2(pair<int,int> a,pair<int,int> b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}
UK uk;
vector<int> link[MAXN];
pair<int,int> pos[MAXN];
int n,dist;
bool repaired[MAXN];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>dist;
    dist=dist*dist;
    for(int i=1;i<=n;i++){
        cin>>pos[i].first>>pos[i].second;
    }

    char op;
    while(cin>>op){
        if(op=='O'){
            int inp;cin>>inp;
            if(repaired[inp])continue;
            repaired[inp]=1;
            for(int i=1;i<=n;i++){
                if(i==inp)continue;
                if(getdist2(pos[inp],pos[i])<=dist){
                    if(repaired[i])uk.con(inp,i);
                }
            }
        }else if(op=='S'){
            int a,b;cin>>a>>b;
            if(repaired[a] && repaired[b] && uk.isc(a,b)){
                cout<<"SUCCESS"<<endl;
            }else{
                cout<<"FAIL"<<endl;
            }
        }
    }

    return 0;
}

