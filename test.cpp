#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
const int MAXV = 50010, MAXE = 50010;
const int MAXQ = 50050;
struct Edge
{
    int v;
    int w;
} edges[MAXE];

int idx = 0;
vector<int> g[MAXV];
inline void adde(int u, int v, int w)
{
    edges[++idx].v = v;
    edges[idx].w = w;
    g[u].push_back(idx);
}

struct Node
{
    ll dist;
    int u;
    int nexte;

    Node(int u, ll dist, int nexte) : u(u), dist(dist), nexte(nexte) {}

    bool operator<(const Node &b) const
    {
        return dist > b.dist;
    }
};
int vlen, elen, qlen;
ll ans[MAXQ];

void solve()
{
    priority_queue<Node> pq;
    for (int u = 1; u <= vlen; u++)
    {
        for (int ei = 0; ei < min((size_t)1, g[u].size()); ei++)
        {
            Edge &e = edges[g[u][ei]];
            pq.push(Node(u, e.w, ei));
        }
    }
    int kth = 0;
    while (!pq.empty() && kth<=5e4+10)
    {
        Node cur = pq.top();
        ans[++kth]=cur.dist;
        pq.pop();

        Edge &e = edges[g[cur.u][cur.nexte]];
        //expand next v
        Node next = cur;
        next.u = e.v;
        next.nexte = 0;
        bool hasnext = 0;
        if (next.nexte < g[next.u].size())
        {
            next.dist += edges[g[next.u][next.nexte]].w;
            pq.push(next);
        }

        bool hascur = 0;
        // no edge to expand current v
        if (cur.nexte + 1 < g[cur.u].size())
        {
            Edge &ne = edges[g[cur.u][cur.nexte + 1]];
            cur.dist -= e.w;
            cur.dist += ne.w;
            cur.nexte++;
            pq.push(cur);
        }
    }
}

int main()
{
    int kase;
    scanf("%d",&kase);
    while (kase--)
    {
        idx = 0;
        scanf("%d%d%d",&vlen,&elen,&qlen);
        for (int i = 0; i <= vlen; i++)
            g[i].clear();

        for (int i = 1; i <= elen; i++)
        {
            int u, v, w;
            scanf("%d%d%d",&u,&v,&w);
            adde(u, v, w);
        }
        for (int i = 1; i <= vlen; i++)
        {
            sort(g[i].begin(), g[i].end(), [](int a, int b) {
                return edges[a].w < edges[b].w;
            });
        }
        solve();

        for (int i = 1; i <= qlen; i++)
        {
            int q;
            scanf("%d",&q);
            printf("%lld\n",ans[q]);
        }
    }
    return 0;
}