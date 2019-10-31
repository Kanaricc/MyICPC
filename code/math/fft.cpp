#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>
#include <cstdlib>
using namespace std;
const double PI=acos(-1);

inline complex<double> gomega(int n,int k,bool rev=false){
    complex<double> res(cos(2*PI/n*k),sin(2*PI/n*k));
    if(rev)return conj(res);
    else return res;
}
const int MAXN=10;
struct FFT{
    complex<double> omega[MAXN],omegaI[MAXN];

    FFT(int n){
        for(int i=0;i<n;i++){
            omega[i]=gomega(n,i);
            omegaI[i]=gomega(n,i,1);
        }
    }
    void transform(complex<double> *a,int n,const complex<double> *omega){
        int k=0;
        while((1<<k)<n)k++;
        for(int i=0;i<n;i++){
            int t=0;
            for(int j=0;j<k;j++)if(i&(1<<j))t|=(1<<(k-j-1));
            if(i<t)swap(a[i],a[t]);
        }
        for(int l=2;l<=n;l*=2){
            int m=l/2;
            for(complex<double> *p=a;p!=a+n;p+=l){
                for(int i=0;i<m;i++){
                    complex<double> t=omega[n/l*i]*p[m+i];
                    p[m+i]=p[i]-t;
                    p[i]+=t;
                }
            }
        }
    }
    void dft(complex<double> *a,int n){
        transform(a,n,omega);
    }
    void idft(complex<double> *a,int n){
        transform(a,n,omegaI);
        for(int i=0;i<n;i++)a[i]/=n;
    }
};



int main(){

    return 0;
}

