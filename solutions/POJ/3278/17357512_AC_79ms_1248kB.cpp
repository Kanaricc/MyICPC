#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN=100010;

struct v4q{
    int p,w;
    v4q(){}
    v4q(int p,int w):p(p),w(w){}
};
bool vis[MAXN];
int solve(int n,int k){
    memset(vis,0,sizeof(vis));
    queue<v4q> q;
    q.push(v4q(n,0));

    while(!q.empty()){
        v4q cur=q.front();
        q.pop();

        if(cur.p<0 || cur.p>MAXN)continue;
        if(vis[cur.p])continue;
        if(cur.p==k)return cur.w;

        vis[cur.p]=1;

        q.push(v4q(cur.p+1,cur.w+1));
        q.push(v4q(cur.p-1,cur.w+1));
        q.push(v4q(cur.p*2,cur.w+1));
    }
    return -1;
}
int main(){
    int n,k;
    while(cin>>n>>k)
        cout<<solve(n,k)<<endl;

    return 0;
}
