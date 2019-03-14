#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;
const int MAXN=500010;

int a[MAXN];
int main(){
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	bool ok=true;

	a[0]=-0x7f7f7f7f;
	int i=1;
	for(;i<=n;i++){
		if(a[i]>a[i-1])continue;
		else break;
	}
	int count=0;
	for(;i<=n;i++){
		if(a[i]==a[i-1]){
			count++;
			continue;
		}else break;
	}

	for(;i<=n;i++){
		if(a[i]<a[i-1])continue;
		else break;
	}
	if(i!=n+1){
		cout<<"NO"<<endl;
	}else{
		cout<<"YES"<<endl;
	}

	return 0;
}