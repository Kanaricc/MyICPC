#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;
using ll=long long;
const int MAXP=1000010;
const ll P=1e9+7;
const ll PHI_P=1e9+6;
const ll INV_6=166666668;

int is_np[MAXP];
int t[MAXP];
ll S[MAXP];
vector<int> primes;

inline int qpow(ll a,ll b,ll p){
    ll res=1;
    for(b;b;b>>=1,a=a*a%p){
        if(b&1)res=res*a%p;
    }
    return res%p;
}

inline int get_inv(ll a,ll p){
    return qpow(a,p-2,p);
}
void init(int nlen){
    is_np[1]=1;
    is_np[2]=0;

    S[1]=1;

    for(int i=2;i<=nlen;i++){
        if(!is_np[i]){
            primes.push_back(i);
            t[i]=1;

            S[i]=((ll)i*i%P-1)%P;
        }
        for(int j=0;j<primes.size(),primes[j]*i<=nlen;j++){
            t[i*primes[j]]=1;
            S[i*primes[j]]=S[i]*S[primes[j]]%P;

            is_np[i*primes[j]]=1;
            if(i%primes[j]==0){
                t[i*primes[j]]=t[i]+1;

                S[i*primes[j]]=(qpow(qpow(primes[j],t[i]+1,P),2,P)-qpow(qpow(primes[j],t[i],P),2,P))*S[i/qpow(primes[j],t[i],P)];
                S[i*primes[j]]%=P;
                break;
            }
        }
    }
}
unordered_map<ll,ll> du;
ll ss[MAXP];
void init_S(int nlen){
    ss[0]=0;
    for(int i=1;i<=nlen;i++){
        ss[i]=(ss[i-1]+S[i])%P;
    }
}

ll du_sieve(ll n){
    if(n<=1000000){
        return ss[n];
    }
    if(du.count(n))return du[n];

    ll res=n%P*(n+1)%P*(2*n+1)%P*INV_6%P;
    for(ll l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        res=(res-(r-l+1)%P*du_sieve(n/l)%P)%P;
    }
    return du[n]=res%P;
}

ll realk,spk;
inline ll fsum(ll a){
    if(a==1){
        return (spk-1)%P;
    }
    return (a*a%P-qpow(a,realk+1,P))%P*get_inv(1-a,P)%P;
}

ll solve(ll n,ll k){
    ll ans=0;
    for(ll l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ans=(ans+fsum(n/l)*(du_sieve(r)-du_sieve(l-1))%P)%P;
    }
    return ans;
}

ll n;
char k[100010];

ll big_mod(char *k,ll p){
    ll res=0;
    for(;*k!='\0';k++){
        res=(res*10+*k-'0')%p;
    }
    return res;
}

int main(){
    init(1000000);
    init_S(1000000);
    int kase;
    scanf("%d",&kase);
    while(kase--){
        //cin>>n>>k;
        scanf("%lld%s",&n,k);
        realk=big_mod(k,PHI_P);
        spk=big_mod(k,P);
        printf("%lld\n",(solve(n,realk)%P+P)%P);
    }
    return 0;
}