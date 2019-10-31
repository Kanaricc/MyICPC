#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
const int MAXV = 110, MAXE = 110*110;
struct Edge {
	int v, n;
} edges[MAXE];
int head[MAXV], idx = 0;
void adde(int u, int v) {
	edges[++idx].v = v;
	edges[idx].n = head[u];
	head[u] = idx;
}
void adee(int u, int v) {
	adde(u, v); adde(v, u);
}
int tick = 0, cpidx = 0;
int dfn[MAXV], low[MAXV];
int instack[MAXV];
int incp[MAXV];
stack<int> cp;
void tarjan(int u) {
	instack[u] = 2;
	dfn[u] = low[u] = ++tick;
	cp.push(u);
	for (int ei = head[u]; ei; ei = edges[ei].n) {
		Edge &e = edges[ei];
		if (dfn[e.v] == 0) {
			tarjan(e.v);
			low[u] = min(low[u], low[e.v]);
		}
		else if (instack[e.v] == 2) {
			low[u] = min(low[u], dfn[e.v]);
		}
	}
	if (low[u] == dfn[u]) {
		cpidx++;
		while (!cp.empty()) {
			int cur = cp.top(); cp.pop();
			instack[cur] = 1;
			incp[cur] = cpidx;
			if (cur == u)break;
		}
	}
}
int ind[MAXV],outd[MAXV];
int main() {
	int vlen; cin >> vlen;
	for (int i = 1; i <= vlen; i++) {
		int v;
		while (cin >> v) {
			if (v == 0)break;
			adde(i, v);
		}
	}
	int res = 0;
	for (int i = 1; i <= vlen; i++) {
		if (!dfn[i])tarjan(i);
	}
	for (int u = 1; u <= vlen; u++) {
		for (int ei = head[u]; ei; ei = edges[ei].n) {
			Edge &e = edges[ei];
			if (incp[u] != incp[e.v]) {
				//TODO:重复计算
				ind[incp[e.v]]++;
				outd[incp[u]]++;
			}
		}
	}
	int sub1 = 0;
	for (int u = 1; u <= cpidx; u++)if (ind[u] == 0)sub1++;

	int sub2 = 0;
	if (cpidx != 1) {
		for (int u = 1; u <= cpidx; u++)if (outd[u] == 0)sub2++;
	}

	cout << sub1 << endl;
	cout << max(sub1,sub2) << endl;
	

	//while (1);
	return 0;
}