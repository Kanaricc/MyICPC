#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
double a,b;
double f(double x){
    return 2*sqrt(b*b*(1-x*x/a/a));
}
inline double fittingf(double l,double r){
    return (f(l)+f(r)+4*f((l+r)/2))*(r-l)/6;
}
double adaptive_simpson(double l,double r,double eps){
    double mid=(l+r)/2;
    double res=fittingf(l,r);
    double lr=fittingf(l,mid),rr=fittingf(mid,r);
    if(abs(lr+rr-res)<15*eps)
        return lr+rr+(lr+rr-res)/15;
    else
        return adaptive_simpson(l,mid,eps/2)+adaptive_simpson(mid,r,eps/2);
}

int main(){
    int kase;cin>>kase;
    while(kase--){
        double l,r;
        cin>>a>>b>>l>>r;
        cout<<fixed<<setprecision(3)<<adaptive_simpson(l,r,1e-7)<<endl;
    }

    return 0;
}
