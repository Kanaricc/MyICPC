#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN=250,MAXV=250;

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
int vlen,elen,plen;

vector<int> plants;
bool isplants[MAXV];
struct v4q{
    int u,v,w;
    v4q(){}
    v4q(int u,int v,int w):u(u),v(v),w(w){}
    bool operator<(const v4q &b)const{
        return w>b.w;
    }
};
int main(){
    int kase;cin>>kase;
    for(int cnt=1;cnt<=kase;cnt++){
        UT ut;
        priority_queue<v4q> pq;
        memset(isplants,0,sizeof(isplants));
        plants.clear();
        cin>>vlen>>elen>>plen;
        for(int i=0;i<plen;i++){
            int id;cin>>id;
            plants.push_back(id);
            isplants[id]=1;
        }
        for(int i=0;i<elen;i++){
            int u,v,w;cin>>u>>v>>w;
            pq.push(v4q(u,v,w));
        }
        //solve
        int ans=0;
        while(!pq.empty()){
            v4q e=pq.top();pq.pop();
            //cout<<e.u<<" "<<e.v<<endl;
            if(ut.isc(e.u,e.v))continue;
            bool oku=false,okv=false;
            for(int j=0;j<plants.size();j++){
                if(ut.isc(plants[j],e.u))oku=1;
                if(ut.isc(plants[j],e.v))okv=1;
            }
            if(!oku && okv){
                swap(oku,okv);
                swap(e.u,e.v);
            }
            if(oku && okv){
                continue;
            }

            else if(oku && !okv){
                if(isplants[okv])continue;
                else{
                    ut.con(e.u,e.v);
                    //cout<<"com"<<endl;
                    ans+=e.w;
                }
            }else{
                //!oku !okv
                if(isplants[e.u] && isplants[e.v])continue;
                ut.con(e.u,e.v);
                //cout<<"com"<<endl;
                ans+=e.w;
            }
        }
        cout<<"Case #"<<cnt<<": "<<ans<<endl;
    }

    return 0;
}
