#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int MAXV=300,MAXE=50;
const int MAXN=50;

struct UT{
    int fa[MAXV];
    UT(){
        for(int i=0;i<MAXN;i++)fa[i]=i;
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
        return w>b.w;
    }
    v4q(){}
    v4q(int u,int v,int w):u(u),w(w),v(v){}
};

priority_queue<v4q> pq;

int MST(priority_queue<v4q> &pq){
    UT ut;
    int res=0;
    while(!pq.empty()){
        v4q cur=pq.top();pq.pop();
        if(!ut.isc(cur.u,cur.v)){
            ut.con(cur.u,cur.v);
            res+=cur.w;
        }
    }
    return res;
}
vector<v4q> vec;
int main(){
    int kase;cin>>kase;
    while(kase--){
        int vlen,elen;cin>>vlen>>elen;
        
        for(int i=0;i<elen;i++){
            int u,v,w;cin>>u>>v>>w;
            if(elen<=1){
                cout<<w<<endl;
            }

            vec.push_back(v4q(u,v,w));
        }
        vector<int> res;
        for(int i=0;i<vec.size();i++){
            for(int j=0;j<vec.size();j++){
                if(i==j)continue;
                pq.push(vec[j]);
            }
            res.push_back(MST(pq));
        }
        sort(res.begin(),res.end());
        if(res[0]!=res[1]){
            cout<<res[0]<<endl;
        }else{
            cout<<"Not Unique!"<<endl;
        }

    }
    return 0;
}

