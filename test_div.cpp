#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include <regex>
#include <cmath>
using namespace std;
const int MAXN=200;

long long getsq(long long x){
    long long l=0,r=x;
    while(l<r-1){
        long long mid=(l+r)/2;
        if(mid*(mid-1)<=x)l=mid;
        else r=mid-1;
    }
    for(int i=l;i<=r;i++){
        if(i*(i-1)==x)return i;
    }
    return -1;
}
bool isvalid_same(long long x){
    return getsq(x*2)!=-1;
}
bool solve(long long oo,long long ll,long long ol,long long lo){
    if(!isvalid_same(oo) || !isvalid_same(ll))return false;
    long long o=getsq(oo*2),l=getsq(ll*2);
    if(o*l!=ol+lo)return false;
    //use 10 to calculate
    while(lo>0){
        while(o>lo){
            cout<<0;
            o--;
        }
        cout<<1;
        l--;
        lo-=o;
    }
    while(o--)cout<<0;
    while(l--)cout<<1;
    cout<<endl;
    return true;
}


int main(){
    long long test;
    while(cin>>test){
        cout<<getsq(test)<<endl;
        }
    ios::sync_with_stdio(false);
    long long oo,ll,ol,lo;
    cin>>oo>>ol>>lo>>ll;   
    if(oo==ll && ll==ol && ol==lo && oo==0){
        cout<<1<<endl;
    }else if(oo!=0 && ll==ol && ol==lo && ll==0){
        long long temp=getsq(oo);
        while(temp--)cout<<0;
        cout<<endl;
    }else if(ll!=0 && oo==ol && ol==lo && oo==0){
        long long temp=getsq(oo);
        while(temp--)cout<<1;
        cout<<endl;
    }else if(!solve(oo,ll,ol,lo)){
        cout<<"impossible"<<endl;
    }

    return 0;
}
