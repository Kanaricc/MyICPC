#include<bits/stdc++.h>
using namespace std;
int u[15],r[15];
struct peo{
	int u,r,s,T;
	void read()
	{
		cin>>u>>r>>s;
		T=u+r;
	}
}p[15];
int main()
{
	for(int i=1;i<=10;i++)
		cin>>u[i]>>r[i];
	for(int i=1;i<=10;i++)
		p[i].read();
	int ans=0;
	int qqq=3;
	while(qqq--)
	{
		for(int i=1;i<=10;i++)
		{
			if(ans<p[i].s)
			{
				p[i].s+=max(0,ans+u[i]-p[i].s);
				ans+=u[i]+r[i];
				continue;
			}
			int x=(ans-p[i].s)%p[i].T;
			if(x<p[i].u)
			{
				ans+=p[i].u-x;
				ans+=u[i]+r[i];
				if(u[i]>p[i].r)
					p[i].s+=u[i]-p[i].r;
				continue;
			}
			else
			{
				ans+=u[i]+r[i];
				int res=p[i].T-x;
				if(u[i]>res)
					p[i].s+=u[i]-res;
			}
		}
	}
	cout<<ans-r[10];
}