#include<cstdio>
#include<cstring>
#include<cstdlib>

struct Node
{
	int a,b,c;
	int id;
	void read(int i)
	{
		scanf("%d%d%d",&a,&b,&c);
		id=i;
	}
};
Node minion[15];
struct Node2
{
	int ID,Type,Cost,Damage,Spell_Power;
	int Target,Round;
	bool Used;
	void read(int i)
	{
		scanf("%d",&Type);
		if(Type==1||Type==2) scanf("%d%d%d",&Cost,&Damage,&Spell_Power);
		else scanf("%d%d",&Cost,&Damage);
		ID=i;
		Target=-1;
	}
};
Node2 card[15];
int n,HP,HP2;
Node2 st[15][15];
int ln[15];
inline int min(int x,int y)
{
	return x<y?x:y;
}
inline int max(int x,int y)
{
	return x>y?x:y;
}
bool Defeat=false;
void dfs(int HP,int HP2,int Mana,int Round,bool Type3,int Spell_Power)
{
	if(Defeat) return;
	if(HP2==0)
	{
		printf("Yes\n");
		for(int i=1;i<=3;i++)
		{
			if(ln[i])
			{
				printf("%d\n",ln[i]);
				for(int j=1;j<=ln[i];j++) printf("%d ",st[i][j].ID);
				printf("\n");
				for(int j=1;j<=ln[i];j++) printf("%d ",st[i][j].Target);
				printf("\n");
			}
			else printf("0\n");
		}
		Defeat=true;
		return;
	}
	if(Round==4) return;
	for(int i=1;i<=n;i++)
	{
		if(card[i].Used==false&&card[i].Cost<=Mana&&(Type3==false||card[i].Type==3))
		{
			st[Round][++ln[Round]]=card[i];
			card[i].Used=true;
			if(card[i].Type==3)
			{
				st[Round][ln[Round]].Target=0;
				dfs(HP,max(0,HP2-card[i].Damage-Spell_Power),Mana-card[i].Cost,Round,true,Spell_Power);
				for(int j=1;j<=3;j++)
				{
					if(minion[j].b) 
					{
						st[Round][ln[Round]].Target=j;
						int tmp=minion[j].b;
						minion[j].b=max(0,minion[j].b-card[i].Damage-Spell_Power);
						dfs(HP,HP2,Mana-card[i].Cost,Round,true,Spell_Power);
						minion[j].b=tmp;
					}
				}
			}
			else
			{
				if(card[i].Type==1)
				{
					int tmp[4]={0};
					for(int j=1;j<=3;j++)
					{
						tmp[j]=minion[j].b;
						minion[j].b=max(0,minion[j].b-card[i].Damage-Spell_Power);
					}
					dfs(HP,HP2,Mana-card[i].Cost,Round,false,Spell_Power+card[i].Spell_Power);
					for(int j=1;j<=3;j++) minion[j].b=tmp[j];
				}
				else dfs(HP,max(0,HP2-card[i].Damage-Spell_Power),Mana-card[i].Cost,Round,false,Spell_Power+card[i].Spell_Power);
			}
			card[i].Used=false;
			ln[Round]--;
		}
	}
	int ATK=0;
	for(int i=1;i<=3;i++) if(minion[i].b) ATK+=minion[i].a;
	if(ATK>=HP) return;
	for(int i=1;i<=3;i++) minion[i].b=minion[i].c;
	dfs(HP-ATK,HP2,10,Round+1,false,0);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		Defeat=false;
		memset(ln,0,sizeof(ln));
		memset(st,0,sizeof(st));
		scanf("%d",&n);
		scanf("%d%d",&HP,&HP2);
		for(int i=1;i<=3;i++)
			minion[i].read(i);
		for(int i=1;i<=n;i++)
			card[i].read(i);
		dfs(HP,HP2,10,1,false,0);
		if(Defeat==false) printf("No\n");
	}
} 