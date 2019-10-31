#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
struct Frac{
    T a,b;
    Frac(T a=0,T b=1):a(a),b(b){}
    static T gcd(T a,T b){
        return !b?a:gcd(b,a%b);
    }
    void simplify(){
        T g=gcd(abs(a),abs(b));
        if(g==0)return;
        a/=g;
        b/=g;
    }
    Frac operator*(const Frac &other)const{
        Frac res=*this;
        res*=other;
        return res;
    }
    Frac operator/(const Frac &other)const{
        Frac res=*this;
        res/=other;
        return res;
    }
    Frac operator+(const Frac &other)const{
        Frac res=*this;
        res+=other;
        return res;
    }
    Frac operator-(const Frac &other)const{
        Frac res=*this;
        res-=other;
        return res;
    }

    Frac& operator+=(const Frac &other){
        a=a*other.b+b*other.a;
        b*=other.b;
        simplify();
        return *this;
    }
    Frac& operator-=(const Frac &other){
        a=a*other.b-b*other.a;
        b*=other.b;
        simplify();
        return *this;
    }
    Frac& operator*=(const Frac &other){
        a*=other.a;
        b*=other.b;
        simplify();
        return *this;
    }
    Frac& operator/=(const Frac &other){
        a*=other.b;
        b*=other.a;
        simplify();
        return *this;
    }
};