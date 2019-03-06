#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_IDX=20;
int a[MAX_IDX];//存元数据
int id[MAX_IDX],idx=0;//节点编号
int root;
int lc[MAX_IDX],rc[MAX_IDX];
int data[MAX_IDX];//节点维护数据
//区间最大值
int build(int &n,int l, int r){
    if(!n)n=++idx;
    data[n]=a[l];
    if(l>=r)return a[l];
    int mid=(l+r)/2;
    //max
    data[n]=max(build(lc[n],l,mid),build(rc[n],mid+1,r));
    return data[n];
}
//查询       查询范围  当前节点范围 当前节点编号
int query(int l,int r,int L,int R,int node){
    if(l<=L && R<=r)return data[node];//查询范围
    int mid=(L+R)/2;
    int res=0;
    //   l在左子节点中
    if(l<=mid)res=max(res,query(l,r,L,mid,lc[node]));
    //  v
    if(r>mid)res=max(res,query(l,r,mid+1,R,rc[node]));
    return res;
}
//记录查询的位置√
int ql,qr;
int query(int l,int r,int node){
	if(l<=ql && qr<r)return data[node];
	int mid=(l+r)/2;
	int res=0;
	if(ql<=mid)res=max(res,query(l,mid,lc[node]));
	if(r>mid)res=max(res,query(mid+1,r,rc[node]));
	
	return res;
}
int main(){
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    build(root,0,n-1);
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++)debug(query(i,j,0,n-1,root));
    }
    return 0;
}
