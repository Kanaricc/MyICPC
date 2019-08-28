#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll=long long;
const int MAXN=50010;

bool isn_p[MAXN];
vector<int> primes;
int mu[MAXN];
int premu[MAXN];
void init_prime(int len){
    isn_p[1]=1;
    mu[1]=1;
    for(int i=2;i<=len;i++){
        if(!isn_p[i]){
            primes.push_back(i);
            mu[i]=-1;
        }

        for(int j=0;j<primes.size() && i*primes[j]<=len;j++){
            isn_p[i*primes[j]]=1;
            mu[i*primes[j]]=mu[i]*-1;

            if(i%primes[j]==0){
                mu[i*primes[j]]=0;
                break;
            }
        }
    }
    premu[0]=0;
    for(int i=1;i<=len;i++)premu[i]=premu[i-1]+mu[i];
}


ll S[MAXN];
void init_S(int len){
    for(int i=1;i<=len;i++){
        for(int l=1,r;l<=i;l=r+1){
            r=i/(i/l);
            S[i]+=(ll)(r-l+1)*(i/l);
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    init_prime(50000);
    init_S(50000);
    int kase;cin>>kase;
    while(kase--){
        int n,m;cin>>n>>m;
        ll ans=0;
        int minn=min(n,m);
        for(int l=1,r;l<=minn;l=r+1){
            r=min(n/(n/l),m/(m/l));
            ans+=S[n/l]*S[m/l]*(premu[r]-premu[l-1]);
        }
        cout<<ans<<endl;
    }

    return 0;
}