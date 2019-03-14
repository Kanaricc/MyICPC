#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int MAXV=300;

struct UT{
    int fa[MAXV];
    UT(){
        for(int i=0;i<MAXV;i++)fa[i]=i;
    }
    int find(int u){
        return fa[u]==u?u:fa[u]=find(fa[u]);
    }
    bool isc(int u,int v){
        return find(u)==find(v);
    }
    void con(int u,int v){
        fa[find(u)]=find(v);
    }
};

struct v4q{
    int u,v,w;
    bool operator<(const v4q &b)const{
        return w<b.w;
    }
    v4q(){}
    v4q(int u,int v,int w):u(u),w(w),v(v){}
};

vector<v4q> edges;
vector<int> used;
int MST(){
    int res=0;
    vector<int> ans;
    sort(edges.begin(),edges.end());
    for(int i=0;i<edges.size();i++){
        UT ut;
        if(!ut.isc(edges[i].u,edges[i].v)){
            ut.con(edges[i].u,edges[i].v);
            res+=edges[i].w;
            used.push_back(i);
        }
    }
    ans.push_back(res);

    for(int i=0;i<used.size();i++){
        UT ut;
        int res=0;
        for(int j=0;j<edges.size();j++){
            if(used[i]==j)continue;
            if(!ut.isc(edges[j].u,edges[j].v)){
                ut.con(edges[j].u,edges[j].v);
                res+=edges[j].w;
            }
        }
        ans.push_back(res);
    }
    sort(ans.begin(),ans.end());
    if(ans[0]==ans[1]){
        return -1;
    }
    return ans[0];
}

int main(){
    int kase;cin>>kase;
    while(kase--){
        int vlen,elen;cin>>vlen>>elen;

        for(int i=0;i<elen;i++){
            int u,v,w;cin>>u>>v>>w;
            edges.push_back(v4q(u,v,w));
        }
        if(elen==1){
            cout<<edges[0].w<<endl;
        }else{
            int ans=MST();
            if(ans==-1){
                cout<<"Not Unique!"<<endl;
            }else{
                cout<<ans<<endl;
            }
        }
    }
    return 0;
}

