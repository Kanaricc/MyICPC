#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

const int MAXN=300000;
const double PI=acos(-1);

inline complex<double> gomega(int n,int k,bool rev=false){
    complex<double> res(cos(2*PI/n*k),sin(2*PI/n*k));
    if(rev)return conj(res);
    else return res;
}
struct FFT{
    complex<double> omega[MAXN],omegaI[MAXN];

    FFT(){
    }
    void init(int n){
        for(int i=0;i<n;i++){
            omega[i]=gomega(n,i);
            omegaI[i]=gomega(n,i,1);
        }
    }

    void transform(complex<double> *a,int n,const complex<double> *omega){
        for(int i=0,j=0;i<n;i++){
            if(i>j)swap(a[i],a[j]);
            //二进制换位
            for(int l=n/2;(j^=l)<l;l>>=1);
        }
        for(int l=2;l<=n;l<<=1){
            int m=l/2;
            for(complex<double> *p=a;p!=a+n;p+=l){
                for(int i=0;i<m;i++){
                    //蝴蝶操作
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

complex<double> a[2][MAXN];
int ans[MAXN];
FFT fft;
int main(){

    int nlen;cin>>nlen;
    int n=1;
    while(n<2*nlen)n*=2;
    fft.init(n);


    for(int i=0;i<2;i++){
        string inp;cin>>inp;
        for(int j=0,k=inp.size()-1;j<inp.size();j++,k--){
            a[i][j]=complex<double>(inp[j]-'0',0);
        }
        fft.dft(a[i],n);
    }
    for(int i=0;i<n;i++)a[0][i]=a[0][i]*a[1][i];
    fft.idft(a[0],n);
    int reslen=nlen+nlen-1;
    for(int i=reslen-1,k=0;i>=0;i--,k++)
        ans[k]=(int)floor(a[0][i].real()+0.5);
    /*
    for(int i=0;i<reslen;i++)cout<<ans[i]<<" ";
    cout<<endl;
    */
    for(int i=0;i<MAXN;i++){
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }
    int ptr=MAXN-1;
    while(ans[ptr]==0)ptr--;
    for(;ptr>=0;ptr--)cout<<ans[ptr];
    cout<<endl;

    return 0;
}

