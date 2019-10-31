#include<bits/stdc++.h>
#define maxn 20005
using namespace std;
struct E{
	int to,nxt;
}b[maxn<<1];
int fst[maxn],tot;
void insert(int f,int t)
{
	b[++tot]=(E){t,fst[f]};fst[f]=tot;
	b[++tot]=(E){f,fst[t]};fst[t]=tot;
}
int n;
int ans[maxn];
int sz[maxn];
bool use[maxn];
void dfs(int x)
{
	use[x]=1;sz[x]=1;
	for(int i=fst[x];i;i=b[i].nxt)
	{
		int v=b[i].to;
		if(!use[v])
		{
			dfs(v);
			sz[x]+=sz[v];
			ans[x]+=sz[v]*(n-sz[v]-1);
		}
	}
	ans[x]+=(sz[x]-1)*(n-sz[x]);
	ans[x]/=2;
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int k=1;k<=T;k++)
	{
		tot=0;
		memset(fst,0,sizeof(fst));
		memset(use,0,sizeof(use));
		memset(ans,0,sizeof(ans));
		int x,y;
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			insert(x,y);
		}
		dfs(1);
		int a=0;
		for(int i=1;i<=n;i++)
			a=max(ans[i],a);
		printf("Case #%d: %d\n",k,a);
	}
}