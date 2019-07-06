#include<cstdio>

const int N=20005;
long long sz[N],sz2[N],Max[N][2];
int a[N*3],tl[N*3],nx[N*3],fa[N],cnt[N];
int t,n,x,y,ln,cj,root;
void dfs(int x)
{
	sz[x]=1;
	for(int i=nx[x];i;i=nx[i])
	{
		if(a[i]==fa[x]) continue;
		fa[a[i]]=x;
		dfs(a[i]);
		if(sz[a[i]]>Max[x][0])
		{
			Max[x][1]=Max[x][0];
			Max[x][0]=sz[a[i]];
		}
		else if(sz[a[i]]>Max[x][1])
			Max[x][1]=sz[a[i]];
		sz[x]+=sz[a[i]];
		sz2[x]+=sz[a[i]]*sz[a[i]];
	}
}
int main()
{
	scanf("%d",&n);
	n++;
	for(int i=1;i<=n;i++)
		tl[i]=++ln;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		x++;y++;
		a[tl[x]=nx[tl[x]]=++ln]=y;
		a[tl[y]=nx[tl[y]]=++ln]=x;
		cnt[x]++,cnt[y]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]>1)
		{
			dfs(i);
			root=i;
			break;
		}
	}
	long long ans=-1;
	for(int i=1;i<=n;i++)
	{
		sz2[i]+=(n-sz[i])*(n-sz[i]);
		if(root!=i)
		{
			if((n-sz[i])>Max[i][0])
			{
				Max[i][1]=Max[i][0];
				Max[i][0]=(n-sz[i]);
			}
			else if((n-sz[i])>Max[i][1])
				Max[i][1]=(n-sz[i]);
		}
		if(ans<((n-1)*(n-1)-sz2[i])/2)
		{
			ans=((n-1)*(n-1)-sz2[i])/2;
			cj=i;
		}
	}
	printf("%lld %lld",ans,ans-Max[cj][0]*Max[cj][1]);
	return 0;
}