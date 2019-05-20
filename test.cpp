#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef double num;
typedef long long ll;
struct Vec{
    ll x,y;
    double _polar;
    Vec(){
        x=y=0;
    }
    Vec(ll x,ll y):x(x),y(y){
        _polar=polar();
    }
    ll dot(const Vec &b)const{
        return x*b.x+y*b.y;
    }
    ll cross(const Vec &b)const{
        return x*b.y-b.x*y;
    }
    double len(){
        return sqrt(sqlen());
    }
    double sqlen(){
        return x*x+y*y;
    }
    Vec normalize(){
        double l=len();
        return Vec(x/l,y/l);
    }
    Vec rotate(double angle){
        return Vec(x*cos(angle)-y*sin(angle),x*sin(angle)+y*cos(angle));
    }
    Vec operator * (double factor)const{
        return Vec(x*factor,y*factor);
    }
    double operator * (const Vec &b)const{
        return cross(b);
    }
    Vec operator - (const Vec &b)const{
        return Vec(x-b.x,y-b.y);
    }
    Vec operator +(const Vec &b)const{
        return Vec(x+b.x,y+b.y);
    }
    double polar()const{
        return atan2(y,x);
    }
    bool leftby(const Vec &b)const{
        return b.cross(*this)>0;
    }
    bool samed(const Vec &b)const{
        return this->cross(b)==0 && this->dot(b)>0;
    }
};
ostream& operator<<(ostream& out,const Vec &b){
    out<<"("<<b.x<<","<<b.y<<")";
    return out;
}
typedef Vec Point;
struct Line{
    Point pos;
    Vec dirc;
    Line(Point pos=Point(0,0),Vec dirc=Vec(0,0)):pos(pos),dirc(dirc){}
    static Line fromPoints(Point a,Point b){
        return Line(a,b-a);
    }
    double getarea(const Line &b)const{
        return abs(dirc.cross(b.dirc));
    }

    Point getintersection(const Line &b)const{
        Vec down=this->pos-b.pos;
        double aa=b.dirc.cross(down);
        double bb=this->dirc.cross(b.dirc);
        return this->pos+this->dirc*(aa/bb);
    }
};

const int MAXN=20010;
Point points[MAXN];
Point v[MAXN*2];
bool cmp(const Point &a,const Point &b){
    return a._polar<b._polar;
}
int main(){ 
    ios::sync_with_stdio(false);

    int n;
    while(cin>>n){
        for(int i=0;i<n;i++){
            cin>>points[i].x>>points[i].y;
        }
        int sumr=0,sumd=0;
        for(int i=0;i<n;i++){
            //cout<<"select "<<points[i]<<endl;
            int idx=0;
            for(int j=0;j<n;j++){
                if(i==j)continue;
                v[idx++]=points[j]-points[i];
            }
            sort(v,v+idx,cmp);
            //for(int i=0;i<v.size();i++)//cout<<v[i]<<" ";
            //cout<<endl;
            int originsize=idx;
            for(int j=0;j<originsize;j++){
                v[idx+j]=v[j];
            }

            int ld=0,le=1;
            int cursize=idx*2;
            for(int j=0;j<originsize;j++){
                //cout<<"choose "<<v[j]<<endl;
                while(le<cursize && (v[le].leftby(v[j]) || le==j))le++;
                while(ld<cursize && ld<le && v[j].dot(v[ld])>0)ld++;
                //cout<<"ld="<<ld<<",le="<<le<<endl;
                sumr+=ld-j-1;
                sumd+=le-ld;
            }
            //cout<<"============="<<endl;
        }
        //cout<<sumr<<","<<sumd<<endl;
        cout<<(sumr-sumd*2)/3<<endl;
    }
    return 0;
}