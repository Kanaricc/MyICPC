#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN=1000000;
typedef long long ll;

ll a[MAXN];
int lc[MAXN],rc[MAXN],idx=0;
int root;
ll data[MAXN];

ll build(int &n,int l,int r){
    if(!n)n=++idx;
    data[n]=a[l];
    if(l>=r) return data[n];
    int mid=(l+r)/2;
    data[n]=build(lc[n],l,mid)+build(rc[n],mid+1,r);
    return data[n];
}
ll flag[MAXN];
void collectchild(int node){
    data[node]=data[lc[node]]+data[rc[node]];
}
void pushdown(int node,int L,int R){
    if(!flag[node])return;
    flag[lc[node]]+=flag[node];
    flag[rc[node]]+=flag[node];

    int mid=(L+R)/2;
    data[lc[node]]+=flag[node]*(mid-L+1);
    data[rc[node]]+=flag[node]*(R-mid);

    flag[node]=0;
}
ll query(int l,int r,int L,int R,int node){
    if(l<=L && R<=r){
        return data[node];
    }
    pushdown(node,L,R);
    ll res=0;
    int mid=(L+R)/2;
    if(l<=mid)res=res+query(l,r,L,mid,lc[node]);
    if(mid<r)res=res+query(l,r,mid+1,R,rc[node]);
    return res;
}

void modify(int l,int r,ll x,int L,int R,int node){
    if(l<=L && R<=r){
        flag[node]+=x;
        data[node]+=x*(R-L+1);
        return;
    }
    pushdown(node,L,R);
    int mid=(L+R)/2;
    if(l<=mid)modify(l,r,x,L,mid,lc[node]);
    if(mid<r)modify(l,r,x,mid+1,R,rc[node]);
    collectchild(node);
}
int main(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(root,1,n);
    int op;
    while(cin>>op){
        if(op==2){
            int l,r;cin>>l>>r;
            cout<<query(l,r,1,n,root)<<endl;
        }else if(op==1){
            int l,r;
            ll x;cin>>l>>r>>x;
            modify(l,r,x,1,n,root);
        }else if(op==0){
            for(int i=1;i<=n;i++){
                cout<<query(i,i,1,n,root)<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
