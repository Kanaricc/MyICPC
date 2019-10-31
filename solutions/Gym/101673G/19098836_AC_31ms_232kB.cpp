#include<cstdio>

int n,m,ans[105];
int food[105],rk[20005];
int dp[105][105][2][2];
inline int max(int x,int y)
{
	return x>y?x:y;
}
inline int min(int x,int y)
{
	return x<y?x:y;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&food[i]);
	rk[0]=m;
	for(int i=1;i<=n;i++)
		rk[i]=rk[i-1]*2/3;
	dp[1][1][0][1]=min(rk[0],food[1]);
	ans[1]=dp[1][1][0][1];
	dp[2][0][1][0]=min(rk[0],food[1]);
	dp[2][1][0][1]=min(rk[0],food[2]);
	dp[2][2][1][1]=min(rk[0],food[1])+min(rk[1],food[2]);
	ans[2]=max(dp[2][1][0][1],dp[2][2][1][1]);
	for(int i=3;i<=n;i++)
	{
		dp[i][0][0][0]=ans[i-2];
		dp[i][0][1][0]=dp[i-1][1][0][1];
		dp[i][1][0][1]=max(dp[i-1][0][1][0],dp[i-1][0][0][0])+min(rk[0],food[i]);
		dp[i][1][1][0]=max(dp[i-1][2][1][1],dp[i-1][2][0][1]);
		ans[i]=max(ans[i],dp[i][0][1][0]);
		ans[i]=max(ans[i],dp[i][1][0][1]);
		ans[i]=max(ans[i],dp[i][1][1][1]);
		for(int j=2;j<=i;j++)
		{
			dp[i][j][0][1]=max(dp[i-1][j-1][1][0],dp[i-1][0][0][0])+min(rk[j-1],food[i]);
			dp[i][j][1][0]=max(dp[i-1][j+1][1][1],dp[i-1][j+1][0][1]);
			dp[i][j][1][1]=max(dp[i-1][j-1][1][1],dp[i-1][j-1][0][1])+min(rk[j-1],food[i]);
			ans[i]=max(ans[i],dp[i][j][0][1]);
			ans[i]=max(ans[i],dp[i][j][1][1]);
			ans[i]=max(ans[i],dp[i][j][1][0]);
		}
		ans[i]=max(ans[i],dp[i][0][0][0]);
	}
	printf("%d",ans[n]);
	return 0;
}