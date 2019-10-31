#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;


const int MAXV = 60010, MAXE = 30010 * 2;
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
} edges[MAXE];
int idx = 0;
vector<int> head[MAXV]; //边集
void addedge(int u, int v, int cap)
{
    head[u].push_back(idx);
    edges[idx++] = Edge(u, v, cap); //正向边
    head[v].push_back(idx);
    edges[idx++] = Edge(v, u, 0); //反向边容量为0,正向边反向边通过异或可以互推
}
int S, T;
int dis[MAXV];
int current[MAXV];
//bfs构造层次图
int BFS(){
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    while (!q.empty()){
        int h = q.front();
        q.pop();
        for (int ei = 0; ei < head[h].size(); ei++){
            Edge &e = edges[head[h][ei]];
            if (e.cap > 0 && dis[e.v] == 0x3f3f3f3f){
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < 0x3f3f3f3f; //是否能够到达汇点
}
//寻找增广路
int dinic(int x, int maxflow){
    if (x == T)
        return maxflow;
    //       ei = current[x] 当前弧优化
    for (int ei = current[x]; ei < head[x].size(); ei++){
        current[x] = ei;
        Edge &e = edges[head[x][ei]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0){
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow){
                e.cap -= flow; //流量降低
                edges[head[x][ei] ^ 1].cap += flow; //流量增加
                return flow;
            }
        }
    }
    return 0; //找不到增广路,退出
}
//启动
int DINIC(){
    int ans = 0;
    //     构造层次图
    while (BFS()){
        memset(current, 0, sizeof(current)); //BFS后应清空当前弧数组
        int flow;
        while (flow = dinic(S, 0x3f3f3f3f)) //进行多次增广
            ans += flow;
    }
    return ans;
}

int cost[MAXV];
int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;int t=m+n+10;
	for(int i=1;i<=n;i++){
		cin>>cost[i];
		addedge(i+m+1,t,cost[i]);
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		int a,b,c;cin>>a>>b>>c;
		sum+=c;
		addedge(1,1+i,c);
		addedge(1+i,m+1+a,0x7f7f7f7f);
		addedge(1+i,m+1+b,0x7f7f7f7f);
	}
	S=1,T=t;
	cout<<sum-DINIC()<<endl;
	
	//cin>>n;
	
	return 0;
}