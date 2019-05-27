#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;
typedef long long ll;
const int MAXN=100010*4;

int a[MAXN];
ll data_max[MAXN],data_min[MAXN];
int data_maxi[MAXN],data_mini[MAXN];
int lc[MAXN],rc[MAXN];
int idx=0;
void collectchild(int id,int L,int R){
    if(data_max[lc[id]]>=data_max[rc[id]]){
        data_max[id]=data_max[lc[id]];
        data_maxi[id]=data_maxi[lc[id]];
    }else{
        data_max[id]=data_max[rc[id]];
        data_maxi[id]=data_maxi[rc[id]];
    }
    if(data_min[lc[id]]<=data_min[rc[id]]){
        data_min[id]=data_min[lc[id]];
        data_mini[id]=data_mini[lc[id]];
    }else{
        data_min[id]=data_min[rc[id]];
        data_mini[id]=data_mini[rc[id]];
    }
}
void build(int &n,int l,int r){
    if(!n)n=++idx;
    data_max[n]=data_min[n]=a[l];
    data_maxi[n]=data_mini[n]=l;
    if(l>=r)return;

    int mid=(l+r)/2;
    build(lc[n],l,mid);
    build(rc[n],mid+1,r);

    collectchild(n,l,r);
}
ll flag[MAXN];
void pushdown(int id,int L,int R){
    if(!flag[id])return;

    flag[lc[id]]+=flag[id];
    flag[rc[id]]+=flag[id];

    data_max[lc[id]]+=flag[id];
    data_max[rc[id]]+=flag[id];
    data_min[lc[id]]+=flag[id];
    data_min[rc[id]]+=flag[id];

    flag[id]=0;
}

void modify(ll x,int l,int r,int L,int R,int id){
    if(l<=L && R<=r){
        flag[id]+=x;
        data_max[id]+=x;
        data_min[id]+=x;
        return;
    }
    pushdown(id,L,R);

    int mid=(L+R)/2;
    if(l<=mid)modify(x,l,r,L,mid,lc[id]);
    if(mid<r)modify(x,l,r,mid+1,R,rc[id]);

    collectchild(id,L,R);
}

pair<int,ll> query_max(int l,int r,int L,int R,int id){
    if(l<=L && R<=r){
        return make_pair(data_maxi[id],data_max[id]);
    }
    pushdown(id,L,R);

    int mid=(L+R)/2;
    ll res=0;
    int resi=0;
    if(l<=mid){
        pair<int,ll> t=query_max(l,r,L,mid,lc[id]);
        if(t.second>=res){
            res=t.second;
            resi=t.first;
        }
    }
    if(mid<r){
        pair<int,ll> t=query_max(l,r,mid+1,R,rc[id]);
        if(t.second>res){
            res=t.second;
            resi=t.first;
        }
    }
    return make_pair(resi,res);
}
pair<int,ll> query_min(int l,int r,int L,int R,int id){
    if(l<=L && R<=r){
        return make_pair(data_mini[id],data_min[id]);
    }
    pushdown(id,L,R);

    int mid=(L+R)/2;
    ll res=numeric_limits<ll>::max();
    int resi=0;
    if(l<=mid){
        pair<int,ll> t=query_min(l,r,L,mid,lc[id]);
        if(t.second<=res){
            res=t.second;
            resi=t.first;
        }
    }
    if(mid<r){
        pair<int,ll> t=query_min(l,r,mid+1,R,rc[id]);
        if(t.second<res){
            res=t.second;
            resi=t.first;
        }
    }
    return make_pair(resi,res);
}

string names[MAXN];
int root=0;
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>names[i];
    for(int i=1;i<=n;i++)a[i]=1;
    build(root,1,n);

    int m;cin>>m;
    while(m--){
        string op;cin>>op;
        if(op=="Battle"){
            int l,r;
            ll p;cin>>l>>r>>p;
            modify(p,l,r,1,n,root);
        }else if(op=="Event"){
            int l;
            ll p;cin>>l>>p;
            modify(p,l,l,1,n,root);
        }else if(op=="BF"){
            int l,r;cin>>l>>r;
            pair<int,ll> res=query_max(l,r,1,n,root);
            cout<<names[res.first]<<" "<<res.second<<endl;
        }else if(op=="GC"){
            int l,r;cin>>l>>r;
            pair<int,ll> res=query_min(l,r,1,n,root);

            cout<<names[res.first]<<" "<<res.second<<endl;

        }else if(op=="Harem?"){
            int l,r;cin>>l>>r;
            if(r-l+1>=50)cout<<"Yes"<<endl;
            else{
                vector<ll> res;
                for(int i=l;i<=r;i++){
                    res.push_back(query_max(i,i,1,n,root).second);
                }
                sort(res.begin(),res.end());
                /*
                for(int i=0;i<res.size();i++){
                    cout<<res[i]<<" ";
                }cout<<endl;
                */
                bool ok=false;
                for(int i=0;i<(int)res.size()-2;i++){
                    if(res[i]+res[i+1]>res[i+2]){
                        ok=true;
                        break;
                    }
                }
                if(ok){
                    cout<<"Yes"<<endl;
                }else cout<<"No"<<endl;
            }
        }
    }

    return 0;
}



