#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef double num;

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
        _polar=atan(y/x);
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
    //得到垂线
    //不会标准化
    Line getppd(){
        return Line(pos+dirc*0.5,dirc.rotate(PI/2));
    }

    Point getintersection(const Line &b)const{
        Vec down=this->pos-b.pos;
        double aa=b.dirc.cross(down);
        double bb=this->dirc.cross(b.dirc);
        return this->pos+this->dirc*(aa/bb);
    }
};

struct Circle{
    Point center;
    Vec radius;
    Circle(Point center,Vec radius):center(center),radius(radius){}
    Circle(Point center,double r){
        this->center=center;
        radius=Vec(r,0);
    }
    Circle(const Line &diameter){
        Point center=diameter.pos;
        center=center+diameter.dirc*0.5;
        this->center=center;
        radius=diameter.dirc*0.5;
    }
    //-1: inner
    //0: on
    //1: outer
    int cover(Point point){
        double t=(point-center).sqlen();
        double r=radius.sqlen();
        return sgn(t-r);
    }
};
// passed in minimum_covering_circle
Circle circumcircle(Point a,Point b,Point c){
    Line l1=Line::fromPoints(a,b);
    Line l2=Line::fromPoints(a,c);
    Line l1p=l1.getppd(),l2p=l2.getppd();
    Point center=l1p.getintersection(l2p);
    return Circle(center,(a-center).len());

}
// passed ensured by 
Circle minimum_covering_circle(vector<Point> &points){
    random_shuffle(points.begin(),points.end());
    Circle C(points[0],0);
    for(int i=1;i<points.size();i++){
        if(C.cover(points[i])<=0)continue;
        C=Circle(points[i],0);
        for(int j=0;j<=i-1;j++){
            if(C.cover(points[j])<=0)continue;
            C=Circle(Line(points[i],points[j]-points[i]));
            for(int k=0;k<=j-1;k++){
                if(C.cover(points[k])<=0)continue;
                C=circumcircle(points[i],points[j],points[k]);
            }
        }
    }
    return C;
}
//index of result starts at 1
vector<Point> convexHull(vector<Point> &points){
    vector<Point> stack;
    stack.push_back(Point(0,0));

    int top=0;//length of stack
    sort(points.begin(),points.end(),[](const Point &a,const Point &b){
            return a.x<b.x || (a.x==b.x && a.y<b.y);
            });

    for(int i=0;i<points.size();i++){
        //cout<<points[i]<<endl;
        //it won't remove points in same line.
        while(top>=2 && (stack[top]-stack[top-1]).leftby(points[i]-stack[top])){
            top--;
            stack.pop_back();
        }
        stack.push_back(points[i]);
        top++;
    }
    int downcaselen=top;
    for(int i=points.size()-1-1;i>=0;i--){
        while(top>=downcaselen+1 && (stack[top]-stack[top-1]).leftby(points[i]-stack[top])){
            top--;
            stack.pop_back();
        }
        stack.push_back(points[i]);
        top++;
    }
    return stack;
}
vector<Point> points;
bool cmp(const Point &a,const Point &b){
    return a.polar()<b.polar();
}
int main(){ 
    int n;
    while(cin>>n){
        vector<Point> p;
        for(int i=0;i<n;i++){
            int x,y;cin>>x>>y;
            p.push_back(Point(x,y));
        }
        vector<Point> hull=convexHull(p);
        for(int i=1;i<hull.size();i++){
            cout<<hull[i]<<endl;
        }
    }

    return 0;
}
