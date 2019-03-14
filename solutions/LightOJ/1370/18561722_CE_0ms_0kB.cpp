#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int MAXN=1000010;
int ans[1000010];

int phi[MAXN];
void init_prime(){
	memset(ans,0x7f,sizeof(ans));
	for(int i=1;i<MAXN;i++)phi[i]=i;
	phi[1]=0;
	for(int i=2;i<MAXN;i++){
		if(phi[i]==i){
			for(int j=i+i;j<MAXN;j+=i){
				phi[j]=phi[j]/i*(i-1);
			}
			phi[i]=i-1;
		}
	}
}
int main(){
    ios::sync_with_stdio(false);
	init_prime();
    for(int i=1;i<MAXN;i++){
		ans[phi[i]]=min(ans[phi[i]],i);
	}
	for(int i=MAXN-1;i>=1;i--){
		ans[i]=min(ans[i],ans[i+1]);
	}
	int kase;cin>>kase;
    for(int i=1;i<=kase;i++){
        int len=0;cin>>len;
		ll ans=0;
		for(int i=0;i<n;i++){
            int a;cin>>a;
			ans+=ans[a];
		}
        cout<<"Case "<<i<<": "<<ans<<" Xukha"<<endl;
	}
    
    return 0;
}

