#include <iostream>
#include <cstring>
#include <queue>
#include <string>
#include <map>
using namespace std;
const int MAXE=20010,MAXV=600;

struct Edge{
    int v,n;
    bool is;
} edges[MAXE];
int head[MAXV],idx=0;
void adde(int u,int v,bool is){
    edges[++idx].v=v;
    edges[idx].is=is;
    edges[idx].n=head[u];
    head[u]=idx;
}
int vis[MAXV];

bool checkis(int S,int T){
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(u==T)return true;
        if(vis[u])continue;
        vis[u]=1;
        for(int ei=head[u];ei;ei=edges[ei].n){
            Edge &e=edges[ei];
            if(!e.is)continue;
            q.push(e.v);
        }
    }
    return false;
}
struct v4q{
    int u;
    bool has;
    v4q(int u,bool has):u(u),has(has){}
};
bool checkhas(int S,int T){
    memset(vis,0,sizeof(vis));
    queue<v4q> q;
    q.push(v4q(S,0));
    bool hash=false;
    while(!q.empty()){
        v4q cur=q.front();q.pop();
        int u=cur.u;
        if(u==T && cur.has)return true;
        if((vis[u]==1 && !cur.has) || vis[u]==2)continue;
        //if(vis[u])continue;
        vis[u]++;
        for(int ei=head[u];ei;ei=edges[ei].n){
            Edge &e=edges[ei];
            q.push(v4q(e.v,cur.has|(e.is==false)));
        }
    }
    return false;
}
map<string,int> mp;
int cnt=1;
int main(){
    ios::sync_with_stdio(false);
    int elen,qlen;cin>>elen>>qlen;
    for(int i=0;i<elen;i++){
        string a,re,b;
        cin>>a>>re>>b;
        if(!mp.count(a))mp[a]=++cnt;
        if(!mp.count(b))mp[b]=++cnt;

        if(re=="is-a"){
            adde(mp[a],mp[b],1);
        }else{
            adde(mp[a],mp[b],0);
        }
    }
    for(int i=1;i<=qlen;i++){
        string a,re,b;
        cin>>a>>re>>b;
        //cout<<mp[a]<<" "<<mp[b]<<endl;
        bool ans=0;
        if(mp.count(a) && mp.count(b)){
            if(re=="is-a"){
                ans=checkis(mp[a],mp[b]);
            }else{
                ans=checkhas(mp[a],mp[b]);
            }
        }else{
            ans=0;
        }
        if(ans){
            cout<<"Query "<<i<<": true"<<endl;
        }else{
            cout<<"Query "<<i<<": false"<<endl;
        }
    }

    return 0;
}
