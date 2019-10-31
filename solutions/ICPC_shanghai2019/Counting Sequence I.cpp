//打表
//跑的太慢

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
using ll=long long;
const int MAXN=3010;
const ll P=1000000007;
int len;
ll fac[MAXN],invFac[MAXN];

ll qpow(ll a,ll b,ll p){
    ll res=1;
    for(;b;b>>=1,a=a*a%p){
        if(b&1)res=res*a%p;
    }
    return res;
}

ll getInv(ll a,ll p){
    return qpow(a,p-2,p);
}


void initFac(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%P;
    }
    for(int i=1;i<=n;i++){
        invFac[i]=getInv(fac[i],P);
    }
}
//ptr指向要填写的位置
int dfs(int ptr,int x,int cnt,ll isum,ll imul,ll mod){
    if(ptr>len){
        if(isum==imul){
            return fac[len]*mod%P;
        }
        return 0;
    }
    int unset=len-ptr+1;
    //cut:当x大于长度
    if(x>len)return 0;
    //cut:积不再增长也无法达到
    if(isum+unset<imul){
        return 0;
    }
    if(imul*x>isum+x+unset-1){
        return 0;
    }


    //填写当前数字
    ll ans=0;
    ans+=dfs(ptr+1,x,cnt+1,isum+x,imul*x,mod*fac[cnt]%P*invFac[cnt+1]%P);
    //+1,枚举下一个数字,但是不填写
    ans+=dfs(ptr,x+1,0,isum,imul,mod);

    return ans%P;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    initFac(3005);

    /*
    int kase;cin>>kase;
    while(kase--){
        int n;cin>>n;
        len=n;
        cout<<dfs(1,1,0,0,1,1)<<'\n';
    }
    */
    cout<<"{";
    for(int i=1;i<=3000;i++){
        len=i;
        cout<<dfs(1,1,0,0,1,1)<<",";
        if(i%100==0){
            cerr<<i<<endl;
        }
    }
    cout<<"}"<<endl;
   

    return 0;
}