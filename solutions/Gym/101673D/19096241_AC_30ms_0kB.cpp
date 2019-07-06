#include<cstdio>

int n,m,x,opt;
int s[105],ln;
void read(int &x,int &opt)
{
	char ch=getchar();
	int sign=1;
	while((ch<'0'||ch>'9')&&ch!='u'&&ch!='-') 
		ch=getchar();
	if(ch=='u')
	{
		ch=getchar();
		opt=1;
		while(ch<'0'||ch>'9') ch=getchar();
		while(ch>='0'&&ch<='9')
		{
			x=x*10+ch-'0';
			ch=getchar();
		}
		return;
	}
	opt=0;
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-')
	{
		sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=sign;
}
int main()
{
	scanf("%d%d",&n,&m);
	int now=0,ans=0;
	for(int i=1;i<=m;i++)
	{
		x=opt=0;
		read(x,opt);
		if(opt==1)
		{
			for(int i=1;i<=x&&ln>0;i++)
			{
				s[ln]=0;
				ln--;
			}
		}
		else s[++ln]=x;
	}
	for(int i=1;i<=ln;i++)
		ans+=s[i];
	printf("%d",(ans%n+n)%n);
	return 0;
} 