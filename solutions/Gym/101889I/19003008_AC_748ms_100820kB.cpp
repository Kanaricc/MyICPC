#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
const int MAXE = 500010,MAXV=300010;
const int MAXP = 30;

int vlen, elen;
struct Edge {
	int v, n, w;
	Edge() {}
	Edge(int v, int n, int w) :v(v), n(n), w(w) {}
} edges[MAXE];
int head[MAXV],idx=0;
inline void adde(int u, int v, int w) {
	edges[++idx].v = v;
	edges[idx].w = w;
	edges[idx].n = head[u];
	head[u] = idx;
}
inline void adee(int u, int v, int w) {
	adde(u, v, w);
	adde(v, u, w);
}

struct UT {
	int fa[MAXV];
	UT() {
		for (int i = 0; i < MAXV; i++)fa[i] = i;
	}
	int find(int u) {
		return fa[u] == u ? u : fa[u] = find(fa[u]);
	}
	bool isc(int u, int v) {
		return find(u) == find(v);
	}
	void con(int u, int v) {
		fa[find(u)] = find(v);
	}
};

struct v4q {
	int u, v, w;
	bool used;
	v4q() {
		used = false;
	}
	v4q(int u, int v, int w) :u(u), v(v), w(w) {
		used = false;
	}
	bool operator<(const v4q &b)const {
		return w > b.w;
	}
};
priority_queue<v4q> pq;
vector<v4q> nerg;
map<pii, int> eref;
inline void cachee(int u, int v, int w) {
	if (u > v)swap(u, v);
	nerg.push_back(v4q(u, v, w));
	eref[make_pair(u, v)] = nerg.size() - 1;
}
v4q* findcache(int u, int v) {
	if (u > v)swap(u, v);
	pii key = make_pair(u, v);
	if (eref.count(key)) {
		return &nerg[eref[key]];
	}
	else return NULL;
}
UT ut;
int ans = 0;

inline void createTree() {
	ans = 0;
	while (!pq.empty()) {
		v4q cur = pq.top(); pq.pop();
		if (ut.isc(cur.u, cur.v))continue;
		//cout << "connect " << cur.u << " " << cur.v << endl;
		ans += cur.w;
		ut.con(cur.u, cur.v);
		findcache(cur.u, cur.v)->used = 1;
		findcache(cur.v, cur.u)->used = 1;
		adee(cur.u, cur.v, cur.w);
	}
}

int P = 0;
int lfa[MAXV][MAXP];
int lw[MAXV][MAXP];
int maxdepth = 0;
int depth[MAXV];
void dfs_fa(int u, int fa,int dep) {
	lfa[u][0] = fa;
	depth[u] = dep;
	maxdepth = max(maxdepth, dep);
	for (int ei = head[u]; ei; ei = edges[ei].n) {
		Edge &e = edges[ei];
		if (e.v == fa)continue;
		lw[e.v][0] = e.w;
		dfs_fa(e.v, u, dep + 1);
	}
}
inline void init_LCA() {
	//init fa
	//random root
	dfs_fa(1, 0, 1);
	for (int len = 1; len < maxdepth; len *= 2, P++);
	for (int p = 1; p <= P; p++) {
		for (int i = 1; i <= vlen; i++) {
			lfa[i][p] = lfa[lfa[i][p - 1]][p - 1];
		}
	}
	for (int p = 1; p <= P; p++) {
		for (int i = 1; i <= vlen; i++) {
			lw[i][p] = max(lw[i][p - 1], lw[lfa[i][p - 1]][p - 1]);
		}
	}
}

int query(int u, int v) {
	int resw = 0;
	int res = 0;
	//approve u is deepper than v
	if (depth[u]<depth[v])swap(u, v);
	//pull u to the same depth of v
	for (int p = P; p >= 0; p--) {
		if (depth[lfa[u][p]] >= depth[v]) {
			resw = max(resw, lw[u][p]);
			u = lfa[u][p];
		}
	}
	//judge if u is v's child.
	if (u == v) {
		res = u;
		return resw;
	}
	//pull in same time.
	for (int p = P; p >= 0; p--) {
		if (lfa[u][p] != lfa[v][p]) {
			resw = max(resw, max(lw[u][p], lw[v][p]));
			u = lfa[u][p];
			v = lfa[v][p];
		}
	}
	//add last one.
	resw = max(resw,max(lw[u][0],lw[v][0]));
	res = lfa[u][0];

	return resw;
}
int main() {
	ios::sync_with_stdio(false);
	cin >> vlen >> elen;
	for (int i = 0; i < elen; i++) {
		int u, v, w; cin >> u >> v >> w;
		pq.push(v4q(u, v, w));
		cachee(u, v, w);
	}
	createTree();
	init_LCA();
	int qlen; cin >> qlen;
	while (qlen--) {
		int u, v; cin >> u >> v;
		v4q *e = findcache(u, v);
		if (e->used) {
			cout << ans << endl;
		}
		else {
			cout << ans-query(u,v)+e->w << endl;
		}
	}


	//while (1);
	return 0;
}