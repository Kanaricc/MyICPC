#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXV = 3010, MAXE = 10000000;
struct Edge {
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap) :u(u), v(v), cap(cap) {}
} edges[MAXE];
int idx = 0;
vector<int> head[MAXV];
void adde(int u, int v, int cap) {
    head[u].push_back(idx);
    edges[idx++] = Edge(u, v, cap);
    head[v].push_back(idx);
    edges[idx++] = Edge(v, u, 0);
}
int s, t;
int dist[MAXV];
bool bfs() {
    queue<int> q;
    fill(dist, dist + MAXV, 0x7f7f7f7f);
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        int cur = q.front();q.pop();
        for (int ei = 0;ei < head[cur].size();ei++) {
            Edge &e = edges[head[cur][ei]];
            if (e.cap > 0 && dist[e.v] == 0x7f7f7f7f) {
                dist[e.v] = dist[e.u] + 1;
                q.push(e.v);
            }
        }
    }
    return dist[t] < 0x7f7f7f7f;
}
int current[MAXV];
int dinic(int u, int maxflow) {
    if (u == t)return maxflow;
    for (int ei = current[u];ei < head[u].size();ei++) {
        current[u] = ei;
        Edge &e = edges[head[u][ei]];
        if (dist[e.v] == dist[u] + 1 && e.cap > 0) {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow) {
                edges[head[u][ei]].cap -= flow;
                edges[head[u][ei] ^ 1].cap += flow;
                return flow;
            }
        }
    }
    return 0;
}
int DINIC() {
    int res = 0;
    while (bfs()) {
        memset(current, 0, sizeof(current));
        int flow = 0;
        while (flow = dinic(s, 0x7f7f7f7f))
            res += flow;
    }
    return res;
}
const int MAXN=3010;
int a[MAXN];
int gcd(int a,int b){
    return !b?a:gcd(b,a%b);
}
set<int> square;
void initsquare(){
    for(int i=1;i<=20000;i++){
        square.insert(i*i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    initsquare();
    int n;cin>>n;
    int isum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        isum+=a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(gcd(a[i],a[j])==1 && square.count(a[i]*a[i]+a[j]*a[j])){
                int ii=i,jj=j;
                if(a[ii]%2==1)swap(ii,jj);
                adde(ii,jj,0x3f3f3f3f);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i]%2==0){
            adde(0,i,a[i]);
        }else{
            adde(i,n+1,a[i]);
        }
    }
    s=0,t=n+1;
    cout<<isum-DINIC()<<endl;
    
    
    //while (1);
    return 0;
}
