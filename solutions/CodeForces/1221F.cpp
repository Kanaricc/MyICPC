#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll=long long;
const int MAXN=500010*4;

ll tag[MAXN];
ll dMax[MAXN];
int dy[MAXN];
int lc[MAXN],rc[MAXN],idx=0;
void build(int &n,int l,int r){
    if(!n)n=++idx;
    dy[n]=r;
    if(l>=r){
        tag[n]=0;
        return;
    }

    int mid=(l+r)/2;
    build(lc[n],l,mid);
    build(rc[n],mid+1,r);
}
void pushdown(int n,int l,int r){
    if(!tag[n])return;
    tag[lc[n]]+=tag[n];
    tag[rc[n]]+=tag[n];
    dMax[lc[n]]+=tag[n];
    dMax[rc[n]]+=tag[n];

    tag[n]=0;
}
void collect(int n){
    if(dMax[lc[n]]>dMax[rc[n]]){
        dMax[n]=dMax[lc[n]];
        dy[n]=dy[lc[n]];
    }else{
        dMax[n]=dMax[rc[n]];
        dy[n]=dy[rc[n]];
    }
}
void modify(int l,int r,int x,int L,int R,int n){
    if(l<=L && R<=r){
        tag[n]+=x;
        dMax[n]+=x;
        return;
    }
    pushdown(n,L,R);

    int mid=(L+R)/2;
    if(l<=mid)modify(l,r,x,L,mid,lc[n]);
    if(mid<r)modify(l,r,x,mid+1,R,rc[n]);
    collect(n);
}

bool operator<(const pair<ll,int> &a,const pair<ll,int> &b){
    return a.first<b.first;
}

pair<ll,int> query(int l,int r,int L,int R,int n){
    if(l<=L && R<=r){
        return make_pair(dMax[n],dy[n]);
    }
    pushdown(n,L,R);
    
    int mid=(L+R)/2;
    pair<ll,int> res=make_pair(-0x3f3f3f3f,0);
    if(l<=mid)res=max(res,query(l,r,L,mid,lc[n]));
    if(mid<r)res=max(res,query(l,r,mid+1,R,rc[n]));

    return res;
}
struct Point{
    int x,y,w;
} points[MAXN];
vector<int> nums;
int root=0;
int main(){
    /*
    build(root,1,10);
    int opt;
    while(cin>>opt){
        if(opt==1){
            int l,r,x;cin>>l>>r>>x;
            modify(l,r,x,1,10,root);
        }
        if(opt==2){
            int l,r;cin>>l>>r;
            cout<<query(l,r,1,10,root).first<<" "<<query(l,r,1,10,root).second<<endl;
        }
    }
    */
    

    int nlen;cin>>nlen;

    for(int i=1;i<=nlen;i++){
        Point &p=points[i];
        cin>>p.x>>p.y>>p.w;
        if(p.x>p.y)swap(p.x,p.y);
        nums.push_back(p.y);
        nums.push_back(p.x);
    }
    sort(nums.begin(),nums.end());
    auto rit=unique(nums.begin(),nums.end());
    for(int i=1;i<=nlen;i++){
        points[i].x=lower_bound(nums.begin(),rit,points[i].x)-nums.begin();
        points[i].y=lower_bound(nums.begin(),rit,points[i].y)-nums.begin();
    }

    sort(points+1,points+1+nlen,[](const Point &a,const Point &b){
        if(a.x!=b.x)return a.x>b.x;
        return a.y<b.y;
    });

    int len=rit-nums.begin()-1;
    build(root,0,len);
    vector<int>::iterator lastit=rit-1;
    pair<ll,int> ans=make_pair(-0x3f3f3f3f,0);
    int pairl=-0x3f3f3f3f;
    for(int i=1;i<=nlen;i++){
        int thisx=points[i].x;
        //auto it=lower_bound(nums.begin(),rit,points[i].x);
        auto it=nums.begin()+thisx;
        for(;lastit!=it;lastit--){
            modify(lastit-nums.begin(),len,*(lastit-1)-*lastit,0,len,root);
            //cout<<"cost "<<*(lastit-1)-*lastit<<" from "<<lastit-nums.begin()<<" to "<<len<<endl;
        }
        /*
        for(int j=0;j<=len;j++){
            cout<<query(j,j,0,len,root).first<<"\t";
        }
        cout<<endl;
        */
        while(i<=nlen && points[i].x==thisx){
            const Point &p=points[i];
            modify(p.y,len,p.w,0,len,root);
            //cout<<"add "<<p.w<<" from "<<p.y<<" to "<<len<<endl;
            i++;
        }
        i--;
        /*
        for(int j=0;j<=len;j++){
            auto temp2=query(j,j,0,len,root);
            cout<<temp2.first<<","<<temp2.second<<"\t";
        }
        cout<<endl;
        */

        pair<ll,int> temp=query(0,len,0,len,root);
        if(ans<=temp){
            ans=temp;
            pairl=nums[thisx];
        }
    }

    if(ans.first>0){
        cout<<ans.first<<endl;
        cout<<pairl<<" "<<pairl<<" "<<nums[ans.second]<<" "<<nums[ans.second]<<endl;
    }else{
        cout<<0<<endl;
        cout<<*nums.rbegin()+1<<" "<<*nums.rbegin()+1<<" "<<*nums.rbegin()+1<<" "<<*nums.rbegin()+1<<endl;
    }
    return 0;
}