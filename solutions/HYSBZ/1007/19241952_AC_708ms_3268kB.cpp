#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
const int MAXN=50010;

struct Line{
    double a,b;
    int i;
    Line(){}
    Line(double a,double b,int i):a(a),b(b),i(i){}
    bool operator<(const Line &other)const{
        if(a==other.a)return b>other.b;
        return a<other.a;
    }
    //return the x of intersection
    double getinter(const Line &other){
        double db=other.b-b;
        double da=a-other.a;
        return db/da;
    }
};

vector<Line> lines;

struct v4s{
    Line *line;
    int li;
    double interx;
    v4s(){}
    v4s(Line *line,double interx):line(line),interx(interx){}
};
stack<v4s> s;
bool jump[MAXN];
int main(){
    int len;cin>>len;
    for(int i=1;i<=len;i++){
        double a,b;cin>>a>>b;
        lines.push_back(Line(a,b,i));
    }
    sort(lines.begin(),lines.end());
    //remove the meaningless lines
    for(int i=1;i<lines.size();i++){
        if(lines[i].a==lines[i-1].a)jump[i]=1;
    }

    for(int i=0;i<lines.size();i++){
        if(jump[i]){
            //cout<<"jump"<<lines[i].a<<","<<lines[i].b<<endl;
            continue;
        }
        while(!s.empty() && s.top().interx>=lines[i].getinter(*(s.top().line)))s.pop();
        if(!s.empty())
            s.push(v4s(&lines[i],lines[i].getinter(*(s.top().line))));
        else
            s.push(v4s(&lines[i],-0x7f7f7f7f));
    }
    vector<int> ans;

    while(!s.empty()){
        ans.push_back(s.top().line->i);
        s.pop();
    }
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
    cout<<endl;

    return 0;
}
