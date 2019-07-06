#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXV = 800, MAXE = 30000;
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
int main() {
    /*
     * 0 start
     * 100-300 cow
     * 400-600 stall
     * 700 dest
     */

    ios::sync_with_stdio(false);
    int cl,sl;
    while(cin>>cl>>sl){
        idx=0;
        for(int i=0;i<MAXV;i++)head[i].clear();
        for(int i=1;i<=cl;i++)adde(0,100+i,1);
        for(int i=1;i<=cl;i++){
            int n;cin>>n;
            for(int j=0;j<n;j++){
                int stall;cin>>stall;
                adde(100+i,400+stall,1);
            }
        }
        for(int i=1;i<=sl;i++){
            adde(400+i,700,1);
        }
        s = 0, t = 700;
        cout << DINIC() << endl;
    }
    //while (1);
    return 0;
}
