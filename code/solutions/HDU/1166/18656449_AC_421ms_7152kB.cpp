#include <iostream>
#include <cstring>
#include <string>
using namespace std;
const int MAXN=500010;

int a[MAXN];
int data[MAXN];
int lc[MAXN],rc[MAXN],idx=0;
int root;
int build(int &n,int l,int r){
    if(!n)n=++idx;
    data[n]=a[l];
    if(l>=r)return data[n];

    int mid=(l+r)/2;
    data[n]=build(lc[n],l,mid)+build(rc[n],mid+1,r);
    return data[n];
}
inline void collectchild(int node){
    data[node]=data[lc[node]]+data[rc[node]];
}
void modify(int l,int r,int x,int L,int R,int node){
    if(l<=L && R<=r){
        //assume 1
        data[node]+=x;
        return;
    }

    int mid=(L+R)/2;
    if(l<=mid)modify(l,r,x,L,mid,lc[node]);
    if(mid<r)modify(l,r,x,mid+1,R,rc[node]);

    collectchild(node);
}

int query(int l,int r,int L,int R,int node){
    if(l<=L && R<=r)return data[node];

    int res=0;
    int mid=(L+R)/2;

    if(l<=mid)res+=query(l,r,L,mid,lc[node]);
    if(mid<r)res+=query(l,r,mid+1,R,rc[node]);

    return res;
}

        

int main(){
    ios::sync_with_stdio(false);
    int kase;cin>>kase;
    for(int i=1;i<=kase;i++){
        cout<<"Case "<<i<<":"<<endl;
        memset(lc,0,sizeof(lc));
        memset(rc,0,sizeof(rc));
        root=0;
        int len;cin>>len;
        for(int i=1;i<=len;i++)cin>>a[i];
        build(root,1,len);

        string op;
        while(cin>>op){
            if(op=="Query"){
                int l,r;cin>>l>>r;
                cout<<query(l,r,1,len,root)<<endl;
            }else if(op=="Add"){
                int pos,x;cin>>pos>>x;
                modify(pos,pos,x,1,len,root);
            }else if(op=="Sub"){
                int pos,x;cin>>pos>>x;
                modify(pos,pos,-x,1,len,root);
            }else if(op=="End"){
                break;
            }
        }
    }

    return 0;
}
