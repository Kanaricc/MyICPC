#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
using ll=long long;
const int P=998244353;

//二次剩余算法
//solve a x to `x^2=a (mod p)` s.t. p is a prime and doesn't divide a
//this alogirthm relys on the posibility.
//expected complexity O(lg^2 n)
inline int Pow(ll x, int y=P-2){
    int ans=1;
    for(; y; y>>=1, x=x*x%P) if(y&1) ans=ans*x%P;
    return ans;
}
inline pair<int,int> pMul(pair<int,int> x, pair<int,int> y, int f){
    return make_pair(
        (int)(((ll)x.first*y.first+(ll)x.second*y.second%P*f)%P),
        (int)(((ll)x.second*y.first+(ll)x.first*y.second)%P)
    );
}
inline int Quadratic_residue(int a){
    if(Pow(a, (P-1)/2)!=1) return -1;
    int x, f;
    do x=(((ll)rand()<<15)^rand())%(a-1)+1; while(Pow(f=((ll)x*x-a+P)%P, (P-1)/2)==1);
    pair<int,int> ans=make_pair(1, 0), t=make_pair(x, 1);
    for(int i=(P+1)/2; i; i>>=1, t=pMul(t, t, f)) if(i&1) ans=pMul(ans, t, f);
    return min(ans.first, P-ans.first);
}

int main(){
    cout<<Quadratic_residue(17)<<endl;

    return 0;
}