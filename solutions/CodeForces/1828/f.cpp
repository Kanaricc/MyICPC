#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
using ll=long long;
constexpr int XN=1000010;
constexpr int XP=20;

vector<int> edges[XN];

int fa[XN][XP],dep[XN];

int t0[XN],t1[XN],tick=0;
void dfs(int u,int f){
    fa[u][0]=f;
    dep[u]=dep[f]+1;
    t0[u]=++tick;
    for(auto v:edges[u]){
        if(v!=f)dfs(v,u);
    }
    t1[u]=++tick;
}
int n;
int ft[XN];
inline int lowbit(int x){
    return x&-x;
}
void ftadd(int pos,int x){
    for(;pos<=tick;pos+=lowbit(pos))ft[pos]+=x;
}
int ftget(int pos){
    int res=0;
    for(;pos>0;pos-=lowbit(pos))res+=ft[pos];
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    int kase;cin>>kase;
    while(kase--){
        cin>>n;
        tick=0;
        for(int i=0;i<=n;i++)edges[i].clear();
        for(int i=2;i<=n;i++){
            int x;cin>>x;
            edges[i].push_back(x);
            edges[x].push_back(i);
        }
        dfs(1,0);
        for(int i=0;i<=tick;i++)ft[i]=0;
        for(int p=1;p<XP;p++){
            for(int i=1;i<=n;i++){
                fa[i][p]=fa[fa[i][p-1]][p-1];
            }
        }

        // 日
        ftadd(t0[1],1);
        int center=1,maxx=0;
        for(int i=2;i<=n;i++){
            ftadd(t0[i],1);
            // cout<<"arr "<<i<<endl;
            if(t0[center]<=t0[i] && t1[i]<=t1[center]){
                // i in the subtree
                int ifa=i;
                for(int p=XP-1;p>=0;p--){
                    if(dep[fa[ifa][p]]>dep[center])ifa=fa[ifa][p];
                }
                int sz=ftget(t1[ifa])-ftget(t0[ifa]-1);
                if(sz>=(i+2-1)/2){
                    center=ifa;
                    maxx=i/2;
                }else maxx=max(maxx,sz);
            }else{
                // out of this subtree
                int sz=i-(ftget(t1[center])-ftget(t0[center]-1));
                if(sz>=(i+2-1)/2){
                    center=fa[i][0];
                    maxx=i/2;
                }else maxx=max(maxx,sz);
            }
            // cout<<"center is "<<center<<endl;
            cout<<i-maxx*2<<" ";
        }
        cout<<"\n";
    }

    return 0;
}