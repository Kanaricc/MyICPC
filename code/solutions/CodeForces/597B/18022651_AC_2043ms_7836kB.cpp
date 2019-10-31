#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
const int MAXN=500010;

int n;
struct Order{
	long long s,e;
	bool operator<(const Order &b)const{
		return e<b.e;
	}
} order[MAXN];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>order[i].s>>order[i].e;
	}
	sort(order+1,order+1+n);

	long long ans=0,ct=0;
	for(int i=1;i<=n;i++){
		if(order[i].s>ct){
			ans++;
			ct=order[i].e;
		}
	}
	cout<<ans<<endl;

	return 0;
}