/*
 * Segment Tree
 * ver 1.0.0
 * node interval: [] (]
 * save data in array.
 *
 * support function:
 * 1. query interval
 * 2. modify interval (using flag)
 *
 * potential bugs:
 * flag doesn't replace data at leaves, which may lead to problems.
 * potential bugs in updating data.
 */
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN=10;

int a[MAXN];
int lc[MAXN],rc[MAXN],idx=0;
int root;
int data[MAXN];

int build(int &n,int l,int r){
    if(!n)n=++idx;
    data[n]=a[l];
    if(l>=r)return data[n];
    int mid=(l+r)/2;
    data[n]=max(build(lc[n],l,mid),build(rc[n],mid+1,r));
    return data[n];
}
void collectchild_n(int node){
    data[node]=max(data[lc[node]],data[rc[node]]);
}
int query_n(int l,int r,int L,int R,int node){
    if(l<=L && R<=r)return data[node];
    int mid=(L+R)/2;
    int res=0;
    if(l<=mid)res=max(res,query_n(l,r,L,mid,lc[node]));
    if(mid<r)res=max(res,query_n(l,r,mid+1,R,rc[node]));
    return res;
}
void modify_noflag(int l,int r,int x,int L,int R,int node){
    if(L>=R){
        data[node]=x;
        return;
    }
    int mid=(L+R)/2;
    if(l<=mid)modify_noflag(l,r,x,L,mid,lc[node]);
    if(mid<r)modify_noflag(l,r,x,mid+1,R,rc[node]);
    collectchild_n(node);
}

int flag[MAXN];
void collectchild(int node){
    int res=-0x7f7f7f7f;

    //we suppose 0 is no flag.
    if(flag[lc[node]])res=max(res,flag[lc[node]]);
    else res=max(res,data[lc[node]]);
    if(flag[rc[node]])res=max(res,flag[rc[node]]);
    else res=max(res,data[rc[node]]);
    data[node]=res;
}
void pushdown(int node){
    if(!flag[node])return;
    flag[lc[node]]=flag[node];
    flag[rc[node]]=flag[node];
    flag[node]=0;
}
int query(int l,int r,int L,int R,int node){
    if(l<=L && R<=r){
        if(flag[node])return flag[node];
        return data[node];
    }
    pushdown(node);
    int res=0;
    int mid=(L+R)/2;
    if(l<=mid)res=max(res,query(l,r,L,mid,lc[node]));
    if(mid<r)res=max(res,query(l,r,mid+1,R,rc[node]));
    return res;
}

void modify(int l,int r,int x,int L,int R,int node){
    if(l<=L && R<=r){
        flag[node]=x;
        return;
    }
    pushdown(node);
    int mid=(L+R)/2;
    if(l<=mid)modify(l,r,x,L,mid,lc[node]);
    if(mid<r)modify(l,r,x,mid+1,R,rc[node]);
    collectchild(node);
}
/*
 * a problem
 * when flag being pushed down to leaves, it doesn't replace data.
 */



int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(root,1,n);
    int op;
    while(cin>>op){
        if(op==1){
            int l,r;cin>>l>>r;
            cout<<query(l,r,1,n,root)<<endl;
        }else if(op==2){
            int l,r,x;cin>>l>>r>>x;
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
