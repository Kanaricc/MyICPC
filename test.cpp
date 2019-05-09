#include <iostream>
#include <cmath>
using namespace std;

int getlen(int x){
    int len=0;
    while(x!=0)len++,x/=10;
    return len;
}

int main(){
    for(int i=1000;i<=100000;i++){
        int len=getlen(i);
        int t=i;
        int isum=0;
        while(t!=0){
            isum+=pow(t%10,len);
            t/=10;
        }
        if(isum==i)cout<<i<<endl;
    }
    return 0;
}
