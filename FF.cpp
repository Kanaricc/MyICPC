#include <iostream>
using namespace std;
const int MAXN=100010;
typedef long long ll;
ll profit[MAXN],cost[MAXN];

int n;
ll need;
bool check(ll day){
    ll isum=0;
    for(int i=0;i<n;i++){
        if(profit[i]*day-cost[i]>0)isum+=profit[i]*day-cost[i];
        if(isum>=need)return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>need;
    
    for(int i=0;i<n;i++)cin>>profit[i]>>cost[i];

    ll l=1,r=4000000000;
    while(l<r){
        ll mid=(l+r)/2;
        if(check(mid))
            r=mid;
        else l=mid+1;
    }
    cout<<r<<endl;

    return 0;
}

