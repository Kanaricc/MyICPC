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

bool isvalid_same(long long x){
    x*=2;
    long long temp=sqrt(x);
    if(temp*(temp+1)!=x)return false;
    return true;
}
bool solve(long long oo,long long ll,long long ol,long long lo){
    if(!isvalid_same(oo) || !isvalid_same(ll))return false;
    long long o=sqrt(oo*2)+1,l=sqrt(ll*2)+1;
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
    ios::sync_with_stdio(false);
    long long oo,ll,ol,lo;
    cin>>oo>>ol>>lo>>ll;   
    if(oo==ll && ll==ol && ol==lo && oo==0){
        cout<<1<<endl;
    }else if(oo!=0 && ll==ol && ol==lo && ll==0){
        long long temp=sqrt(oo*2)+1;
        if(isvalid_same(oo)){
        while(temp--)cout<<0;
        cout<<endl;
        }else{
            cout<<"impossible"<<endl;
        }
    }else if(ll!=0 && oo==ol && ol==lo && oo==0){
        long long temp=sqrt(ll*2)+1;
        if(isvalid_same(ll)){
        while(temp--)cout<<1;
        cout<<endl;
        }else{
            cout<<"impossible"<<endl;
        }
    }else if(!solve(oo,ll,ol,lo)){
        cout<<"impossible"<<endl;
    }

    return 0;
}
