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
int vlen,elen;
int MST(){
    int firstans=0;
    used.clear();
    sort(edges.begin(),edges.end());
    UT ut;
    for(int i=0;i<edges.size();i++){
        if(!ut.isc(edges[i].u,edges[i].v)){
            ut.con(edges[i].u,edges[i].v);
            firstans+=edges[i].w;
            used.push_back(i);
        }
    }

    for(int i=0;i<used.size();i++){
        UT ut;
        int res=0;
        int count=0;
        for(int j=0;j<edges.size();j++){
            if(used[i]==j)continue;
            if(!ut.isc(edges[j].u,edges[j].v)){
                ut.con(edges[j].u,edges[j].v);
                res+=edges[j].w;
                count++;
            }
        }
        if(count!=used.size()){
            //cout<<"cant!"<<endl;
            continue;
        }
        if(res==firstans){
            return -1;
        }
    }
    return firstans;
}

int main(){
    int kase;cin>>kase;
    while(kase--){
        cin>>vlen>>elen;
        edges.clear();

        for(int i=0;i<elen;i++){
            int u,v,w;cin>>u>>v>>w;
            edges.push_back(v4q(u,v,w));
        }

        int ans=MST();
        if(ans==-1){
            cout<<"Not Unique!"<<endl;
        }else{
            cout<<ans<<endl;
        }
    }
    return 0;
}

