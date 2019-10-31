#include <iostream>
#include <unordered_map>
#include <map>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=10;

int game[MAXN][MAXN];
const int POW[]= {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

int pow(int x,int a){
    int res=1;
    for(int i=0;i<a;i++)res*=x;
    return res;
}
void unpack(int x){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            game[i][j]=x/POW[3*3-1-(i*3+j)]%10;
        }
    }
}
int pack(){
    int res=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            res=res*10+game[i][j];
        }
    }
    return res;
}
int evaluate(){
    int res=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int bind=game[i][j]-1;
            int px=bind/3,py=bind%3;
            int dist=abs(px-i)+abs(py-j);
            res+=dist;
        }
    }
    return -res;
}
const int OF[][2]={{1,0},{-1,0},{0,1},{0,-1}};
const char OFN[]={'u','d','l','r'};
unordered_map<int,bool> vis;
unordered_map<int,int> questions;
unordered_map<int,string> cache;
struct v4q{
    int state;
    string path;
    int point;
    v4q(){}
    v4q(int state,string path,int point):state(state),path(path),point(point){}

    bool operator<(const v4q &other)const{
        return point<other.point;
    }
};
int qlen;
void solve(){
    vis.clear();

    queue<v4q> q;
    unpack(123456780);
    q.push(v4q(123456780,"",evaluate()));

    while(!q.empty()){
        v4q node=q.front();q.pop();
        int cur=node.state;
        //cout<<cur<<endl;
        if(vis[cur])continue;
        vis[cur]=1;
        if(questions[cur]){
            cache[cur]=node.path;
            qlen-=questions[cur];
            if(qlen==0)break;
        }

        int x0,y0;
        unpack(cur);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(game[i][j]==0){
                    x0=i,y0=j;
                    break;
                }
            }
        }
        for(int i=0;i<4;i++){
            unpack(cur);
            int ox=x0+OF[i][0],oy=y0+OF[i][1];
            if(ox<0 || ox>=3 || oy<0 || oy>=3)continue;
            swap(game[x0][y0],game[ox][oy]);
            q.push(v4q(pack(),node.path+OFN[i],evaluate()));
        }
    }
}


vector<int> q;
int main(){
    ios::sync_with_stdio(false);
    char x;
    while(cin>>x){
        int tick=0;
        do{
            if(x=='x')game[tick/3][tick%3]=0;
            else game[tick/3][tick%3]=x-'0';
            tick++;
            if(tick>=3*3)break;
        }while(cin>>x);
        questions[pack()]++;
        q.push_back(pack());
        qlen++;
    }
    solve();
    for(auto it=q.begin();it!=q.end();it++){
        if(vis[*it]){
            string str=cache[*it];
            reverse(str.begin(),str.end());
            cout<<str<<endl;
        }else{
            cout<<"unsolvable"<<endl;
        }
    }

    return 0;
}
