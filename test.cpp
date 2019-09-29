#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
const int MAXN=10;

const double EPS=1e-7;
const double PI=acos(-1);
int sgn(double x){
    return (x>-EPS)-(x<EPS);
}
struct Vec{
    double x,y;//never change it yourself unless you dont need polar angle.
    double _polar;// make cache to accumulate speed as atan is too slow.

    Vec(){
        x=y=0;
    }
    Vec(double x,double y):x(x),y(y){
        _polar=atan2(y,x);
    }
    double dot(const Vec &b)const{
        return x*b.x+y*b.y;
    }
    double cross(const Vec &b)const{
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
        return _polar;
    }
    bool leftby(const Vec &b)const{
        return sgn(b.cross(*this))>0;
    }
    bool samed(const Vec &b)const{
        return sgn(this->cross(b))==0 && sgn(this->dot(b))>0;
    }
    bool operator<(const Vec &b)const{
        return this->polar()<b.polar();
    }
};
ostream& operator<<(ostream& out,const Vec &b){
    out<<"("<<b.x<<","<<b.y<<")"<<b.polar();
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
    // 获得垂线
    Line getppd(){
        return Line(pos+dirc*0.5,dirc.rotate(PI/2));
    }

    //TODO: what will happen if they have no intersection,-nan
    Point getintersection(const Line &b)const{
        Vec down=this->pos-b.pos;
        double aa=b.dirc.cross(down);
        double bb=this->dirc.cross(b.dirc);
        return this->pos+this->dirc*(aa/bb);
    }

    bool point_on_line(Point point){
        if(!dirc.samed(point-pos))
        return false;
        if(sgn((point-pos).sqlen()-dirc.sqlen())>0)
        return false;
        return true;
    }

    double get_distance(Point point){
        Line ppd=getppd();
        ppd.pos=point;

        Point intersection=getintersection(ppd);

        ppd.dirc=intersection-point;
        Vec v=intersection-pos;

        return abs(v.cross(point-pos)/v.len());
    }

    double get_distance(Line line){
        return get_distance(line.pos);
    }
};
struct P{
    int i;
    Point p;
    bool origin;
    P(Point p,bool origin,int i=0):p(p),origin(origin),i(i){}
};
vector<P> points;
int ans[MAXN];
int main(){
    int nlen,qlen;cin>>nlen>>qlen;
    for(int i=0;i<nlen;i++){
        int x,y;cin>>x>>y;
        points.push_back(P(Point(x,y),1));
    }
    for(int i=0;i<qlen;i++){
        int x,y;cin>>x>>y;
        points.push_back(P(Point(x,y),0));
    }
}