#include <iostream>
#include <algorithm>
using namespace std;

unsigned int bitrev(unsigned int n){
    unsigned int res=0;
    for(int i=0;i<32;i++){
        res=(res<<1)+(n&1);
        n>>=1;
    }
    return res;
}
int main(){
    unsigned int n;
    cin>>n;
    cout<<bitrev(n)<<endl;

    return 0;
}
    
