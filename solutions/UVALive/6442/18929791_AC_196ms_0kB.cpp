#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int MAXN=20010;

int coins[MAXN];
int len,clen;
bool check(int x){
    int seq=len/clen;
    int lastl=coins[1]-x,lasth=coins[1]+x;
    for(int i=2;i<=clen;i++){
        int curl=max(lastl+seq,coins[i]-x);
        int curh=min(lasth+seq,coins[i]+x);
        if(curl>curh)return false;
        lastl=curl;lasth=curh;
    }
    return true;
}

int main(){
    int kase;cin>>kase;
    for(int ki=1;ki<=kase;ki++){
        cin>>len>>clen;
        for(int i=1;i<=clen;i++){
            cin>>coins[i];
        }
        sort(coins+1,coins+1+clen);

        int l=0,r=len;
        while(l<r){
            int mid=(l+r)/2;
            if(check(mid)){
                r=mid;
            }else l=mid+1;
        }
        cout<<"Case #"<<ki<<": "<<l<<endl;
    }
    return 0;
}
