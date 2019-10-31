#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN=600000;

int game[MAXN];
int getToken(string x){
    for(int i=0;i<x.size();i++){
        x[i]='0'+(x[i]-'0')%2;
    }
    int res=0;
    int base=1;
    for(int i=x.size()-1;i>=0;i--){
        res+=(x[i]-'0')*base;
        base*=2;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    int n;cin>>n;
    while(n--){
        char opt;string num;
        cin>>opt>>num;
        if(opt=='+')game[getToken(num)]++;
        else if(opt=='-')game[getToken(num)]--;
        else if(opt=='?')cout<<game[getToken(num)]<<endl;
    }
    return 0;
}
