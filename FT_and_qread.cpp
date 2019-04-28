#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
typedef long long ll;
const int MAXN=50010;
const int MAXKIND=1000010;
const int MAXQ=200010;
int nex[MAXN];

int kind[MAXN];
int ost[MAXKIND];


template<class T>
inline void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = 1; if (ch == EOF) return; ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + (ch - '0'); ch = getchar(); } if (f) x = -x;
}

const int MAXFT=500000;
int ft[MAXFT];
inline int lowbit(int x) {
    return x&-x;
}
inline void ftadd(int pos, int x) {
    while (pos <= MAXN) {
        ft[pos] += x;
        pos += lowbit(pos);
    }
}
inline ll ftget(int pos) {
    ll res = 0;
    while (pos != 0) {
        res += ft[pos];
        pos -= lowbit(pos);
    }
    return res;
}

struct Query{
    int l,r;
    int ans;
    int i;
    bool operator<(const Query &other)const{
        if(l==other.l)return r<other.r;
        return l<other.l;
    }
} ques[MAXQ];
bool cmp_i(const Query &a,const Query &b){
    return a.i<b.i;
}
int kindptr[MAXKIND];
int main(){
    int n;read(n);
    for(int i=1;i<=n;i++){
        read(kind[i]);
        if(ost[kind[i]]!=0){
            nex[ost[kind[i]]]=i;
        }else{
            //first appear
            kindptr[kind[i]]=i;
            ftadd(i,1);
        }
        ost[kind[i]]=i;
    }
    /*
       for(int i=1;i<MAXKIND;i++){
       if(kindptr[i]!=0){
       cout<<kindptr[i]<<" ";
       }
       }
       cout<<endl;
       for(int i=1;i<=n;i++){
       cout<<nex[i]<<" ";
       }
       cout<<endl;
       */

    int qlen;read(qlen);
    for(int i=0;i<qlen;i++){
        read(ques[i].l);read(ques[i].r);
        ques[i].i=i;
    }
    sort(ques,ques+qlen);

    int lastl=0;
    for(int i=0;i<qlen;i++){
        int l=ques[i].l;
        for(int j=lastl;j<l;j++){
            if(j==0)continue;
            if(nex[j]!=0 && kindptr[kind[j]]<l){
                //ftadd(kindptr[kind[j]],-1);
                kindptr[kind[j]]=nex[j];
                ftadd(kindptr[kind[j]],1);
            }
        }
        ques[i].ans=ftget(ques[i].r)-ftget(ques[i].l-1);
        lastl=l;
    }
    sort(ques,ques+qlen,cmp_i);
    for(int i=0;i<qlen;i++){
        printf("%d\n",ques[i].ans);
    }   

    return 0;
}


