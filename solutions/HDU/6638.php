#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
using ll=long long;
constexpr int MAXN=400010;

ll d_sub[MAXN],d_pre[MAXN],d_suf[MAXN];
ll d_sum[MAXN];
int lc[MAXN],rc[MAXN];
int idx=0;
void build(int &n,int l,int r){
    if(!n)n=++idx;
    d_sum[n]=d_sub[n]=d_pre[n]=d_suf[n]=0;
    if(l==r){
        return;
    }
    int mid=(l+r)/2;
    build(lc[n],l,mid);
    build(rc[n],mid+1,r);
    //combine data
}
void collect(int node){
    d_sum[node]=d_sum[lc[node]]+d_sum[rc[node]];

    d_pre[node]=max(d_pre[lc[node]],d_sum[lc[node]]+d_pre[rc[node]]);
    d_suf[node]=max(d_suf[rc[node]],d_sum[rc[node]]+d_suf[lc[node]]);

    d_sub[node]=max(max(d_sub[lc[node]],d_sub[rc[node]]),d_suf[lc[node]]+d_pre[rc[node]]);
}

void modify(int x,int l,int r,int L,int R,int node){
    if(l<=L && R<=r){
        //only single point to modify
        d_sub[node]=d_sub[node]+x;
        d_pre[node]=d_pre[node]+x;
        d_suf[node]=d_suf[node]+x;
        d_sum[node]+=x;
        return;
    }
    int mid=(L+R)/2;
    if(l<=mid)modify(x,l,r,L,mid,lc[node]);
    if(mid<r)modify(x,l,r,mid+1,R,rc[node]);

    collect(node);
}
int root;
ll query_all(){
    return d_sub[root];
}

struct Chest{
    int x,y,v;
    bool operator<(const Chest &other)const{
        if(x==other.x)return y<other.y;
        return x<other.x;
    }
} chests[MAXN];

vector<int> refy;
int main(){
    /*
    build(root,1,10);
    int opt;
    while(cin>>opt){
        if(opt==1){
            cout<<query_all()<<endl;
        }else{
            int pos,x;cin>>pos>>x;
            modify(x,pos,pos,1,10,root);
        }
    }
    */
    ios::sync_with_stdio(false);
    int kase;cin>>kase;
    while(kase--){
        int nlen;cin>>nlen;
        refy.clear();
        for(int i=0;i<nlen;i++){
            Chest &chest=chests[i];
            cin>>chest.x>>chest.y>>chest.v;
            refy.push_back(chest.y);
        }
        sort(chests,chests+nlen);

        sort(refy.begin(),refy.end());
        auto refyend=unique(refy.begin(),refy.end());
        int maxy=0;
        for(int i=0;i<nlen;i++){
            chests[i].y=lower_bound(refy.begin(),refyend,chests[i].y)-refy.begin()+1;
            maxy=max(maxy,chests[i].y);
        }

        //debug
        /*
        for(int i=0;i<nlen;i++){
            cout<<chests[i].x<<" "<<chests[i].y<<endl;
        }
        */

        int lastx=0;
        ll ans=0;

        //shaobing
        //chests[nlen].x=chests[nlen].y=chests[nlen].v=0;
        for(int i=0;i<nlen;i++){
            if(lastx==chests[i].x)continue;
            lastx=chests[i].x;
            //cout<<"start from "<<lastx<<endl;

            build(root,1,maxy);
            int nextx=chests[i].x;
            for(int j=i;j<nlen;j++){
                if(chests[j].x!=nextx){
                    //cout<<"end at "<<nextx<<endl;
                    //cout<<"ans is "<<query_all()<<endl;
                    nextx=chests[j].x;
                    ans=max(ans,query_all());
                }
                modify(chests[j].v,chests[j].y,chests[j].y,1,maxy,root);
            }
            ans=max(ans,query_all());
            //cout<<"ans is "<<query_all()<<endl;
        }
        cout<<max(0ll,ans)<<endl;
    }

    return 0;
}

