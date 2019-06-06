#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN=110;

const double EPS=1e-8;

struct Point{
    double x,y,z;
    Point(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
    Point operator-(const Point &b)const{
        return Point(x-b.x,y-b.y,z-b.z);
    }
    double dist(const Point &b)const{
        double dx=x-b.x,dy=y-b.y,dz=z-b.z;
        return sqrt(dx*dx+dy*dy+dz*dz);
    }
};

int n;
Point p[MAXN];
double SA(Point start){
    const double DELTA=1000;
    double delta=DELTA;
    double ans=1e20;
    while(delta>EPS){
        int d=0;
        for(int i=0;i<n;i++){
            if(p[i].dist(start)>p[d].dist(start))d=i;
        }
        double r=p[d].dist(start);
        ans=min(ans,r);
        start.x+=(p[d].x-start.x)*delta/DELTA;
        start.y+=(p[d].y-start.y)*delta/DELTA;
        start.z+=(p[d].z-start.z)*delta/DELTA;
        delta*=0.98;
    }
    return ans;
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>p[i].x>>p[i].y>>p[i].z;
    }

    cout<<fixed<<setprecision(8)<<SA(Point(0,0,0))<<endl;

    return 0;
}
