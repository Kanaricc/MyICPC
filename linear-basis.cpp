#include <iostream>
using namespace std;
using ll=long long;

constexpr int MAXN=60;
constexpr int MAXBASE=60;

ll num[MAXN];
ll basis[MAXBASE];

int nlen;
int cal(){
    for(int i=0;i<nlen;i++){
        for(int j=MAXBASE-1;j>=0;j--){
            if(num[i]>>j&1){
                if(basis[j])num[i]^=basis[j];
                else{
                    basis[j]=num[i];
                    for(int k=j-1;k>=0;k--)if((basis[j]>>k&1) && basis[k])basis[j]^=basis[k];
                    for(int k=j+1;k<MAXBASE;k++)if(basis[k]>>j&1)basis[k]^=basis[j];
                    break;
                }
            }
        }
    }
    return 0;
}


        

int main(){
    cin>>nlen;
    for(int i=0;i<nlen;i++)cin>>num[i];
    cal();
    ll ans=0;
    for(int i=0;i<MAXBASE;i++)ans^=basis[i];
    cout<<ans<<endl;

    return 0;
}
