/* CODEFORCES 1221F
 * 题目要求在一个平面坐标系的y=x上确定一正方形的左下角和右上角的点.要求该正方形框住的点的权值和减去正方形边长最大.
 * 可以发现,当一个点x与y坐标的较小的大于l,较大的小于r,该点就位于lr所确定的正方形中.
 * 二维偏序问题.将点按照x坐标排序后,使用一个树状数组来维护到某个y坐标的权值和.
 * 寻找所有权值前缀和的最大值即可.
 * 
 * 这个代码的问题在于,还没有离散化
 */


#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN=50;

int dPre[MAXN],dSum[MAXN];
int dy[MAXN];
int lc[MAXN],rc[MAXN],idx=0;

void build(int &n,int l,int r){
    if(!n)n=++idx;
    if(l>=r){
        dPre[n]=dSum[n]=0;
        dy[n]=r;
        return;
    }

    int mid=(l+r)/2;
    build(lc[n],l,mid);
    build(rc[n],mid+1,r);
}

void collect(int n){
    dSum[n]=dSum[lc[n]]+dSum[rc[n]];
    if(dPre[lc[n]]-dy[lc[n]]>dSum[lc[n]]+dPre[rc[n]]-dy[rc[n]]){
        dPre[n]=dPre[lc[n]];
        dy[n]=dy[lc[n]];
    }else{
        dPre[n]=dSum[lc[n]]+dPre[rc[n]];
        dy[n]=dy[rc[n]];
    }
}

void modify(int p,int x,int L,int R,int n){
    if(p==L && p==R){
        dSum[n]+=x;
        dPre[n]=max(0,dSum[n]);
        return;
    }

    int mid=(L+R)/2;
    if(p<=mid)modify(p,x,L,mid,lc[n]);
    if(mid<p)modify(p,x,mid+1,R,rc[n]);

    collect(n);
}

pair<int,int> query(int l,int r,int L,int R,int n){
    if(l<=L && R<=r){
        return make_pair(dPre[n],dy[n]);
    }

    int mid=(L+R)/2;
    pair<int,int> res;
    if(l<=mid)res=max(res,query(l,r,L,mid,lc[n]));
    if(mid<r)res=max(res,query(l,r,mid+1,R,rc[n]));
    return res;
}
struct Point{
    int x,y,w;
}points[MAXN];
int root;
int main(){
    int nlen;cin>>nlen;
    int miny=0x3f3f3f3f,maxy=-0x3f3f3f3f;
    for(int i=1;i<=nlen;i++){
        Point &p=points[i];
        cin>>p.x>>p.y>>p.w;
        if(p.x>p.y)swap(p.x,p.y);
        miny=min(miny,p.y);
        maxy=max(maxy,p.y);
    }
    sort(points+1,points+1+nlen,[](const Point &a,const Point &b){
        if(a.x!=b.x)return a.x<b.x;
        return a.y<b.y;
    });

    build(root,miny,maxy);

    int ans=0;
    
    for(int i=nlen;i>=1;i--){
        int thisx=points[i].x;
        while(i>=1 && points[i].x==thisx){
            Point &p=points[i];
            cout<<"add "<<p.w<<" to "<<p.y<<endl;
            modify(p.y,p.w,miny,maxy,root);
            i--;
        }
        i++;

        pair<int,int> res=query(miny,maxy,miny,maxy,root);
        cout<<res.first<<" "<<res.second<<endl;
        if(res.second>=thisx)ans=max(ans,res.first-res.second+thisx);
    }
    cout<<ans<<endl;

}