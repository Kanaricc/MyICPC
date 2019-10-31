#include<bits/stdc++.h>
using namespace std;
char s[100005];
int main()
{
	scanf("%s",s+1);
	int l=strlen(s+1);
	int n=l/2;
	int x=0,y=0;
	for(int i=1;i<=n;i++)
		x+=s[i]-'A';
	for(int i=1;i<=n;i++)
	{
		int p=s[i]-'A';
		p=(p+x)%26;
		s[i]=p+'A';
	}
	for(int i=n+1;i<=l;i++)
		y+=s[i]-'A';
	for(int i=n+1;i<=l;i++)
	{
		int p=s[i]-'A';
		p=(p+y)%26;
		s[i]=p+'A';
	}
	for(int i=1;i<=n;i++)
	{
		int p=s[i]-'A';
		p+=s[i+n]-'A';
		p%=26;
		printf("%c",p+'A');
	}
}