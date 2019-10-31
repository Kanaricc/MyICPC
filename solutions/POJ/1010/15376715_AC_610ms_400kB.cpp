#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int alen,blen,a[66],b[66],jy,jyy[66],vis[66];
bool tied,printed;
void dfs(int max_kind,int min_num,int max_money,int x,int pre)
{
    if(min_num>4) return;//不能选四张以上的邮票
    if(x==jy)//和b[i]的值相等
    {
        if(max_kind>jyy[alen+1])//jyy[alen+1]表示kind的最大值
        {
            tied=false;//如果有新的解，要把tied赋值成false
            for(int i=1;i<=alen;i++)
                jyy[i]=vis[i];
            jyy[alen+1]=max_kind;
            jyy[alen+2]=min_num;
            jyy[alen+3]=max_money;
        }
        else if(max_kind==jyy[alen+1])
        {
            if(min_num<jyy[alen+2])//jyy[alen+2]表示num的最小值
            {
                for(int i=1;i<=alen;i++)
                    jyy[i]=vis[i];
                jyy[alen+2]=min_num;
                jyy[alen+3]=max_money;
                tied=false;
            }
            else if(min_num==jyy[alen+2])
            {
                if(max_money>jyy[alen+3])////jyy[alen+3]表示money的最大值
                {
                    for(int i=1;i<=alen;i++)
                        jyy[i]=vis[i];
                    jyy[alen+3]=max_money;
                    tied=false;

                }
                else if(max_money==jyy[alen+3])
                    tied=true;
            }
        }
    }
    int temp;
    for(int i=pre;i<=alen;i++)//i从pre开始，（技巧剪枝）
    {
        if(vis[i]<=4)
        {
            if(!vis[i])max_kind++;//多少种
            vis[i]+=1;
            if(max_money<=a[i])
            {
                max_money=a[i];
                temp=max_money;
            }
            dfs(max_kind,min_num+1,max_money,x+a[i],i);
            vis[i]=vis[i]-1;
            if(vis[i]==0)
            {
                max_kind--;
                if(a[i]==max_money)
                {
                    a[i]=temp;
                }
            }
        }
    }
}

int main()
{
    scanf("%d",&a[1]);//比较坑的循环方式
    start:
        tied=false;
        for(int i=2;;i++)//读入  不解释
        {
            scanf("%d",&a[i]);
            if(a[i]==0)
            {
                alen=i-1;
                break;
            }
        }
        sort(a+1,a+1+alen);//从小到大排序，为了剪枝
        for(int i=1;;i++)
        {
            scanf("%d",&b[i]);
            if(b[i]==0)
            {
                blen=i-1;
                break;
            }
        }
        for(int i=1;i<=blen;i++)
        {
            tied=printed=0;
            jyy[alen+2]=0x3f3f3f3f;//num是选最小值的，所以赋值成极大值
            memset(vis,0,sizeof(vis));
            memset(jyy,0,sizeof(jyy));
            jy=b[i];
            dfs(0,0,0,0,1);//pre要从1开始
            if(tied) printf("%d (%d): tie\n",jy,jyy[alen+1]);
            else
            {
                for(int i=1;i<=alen;i++)
                    if(jyy[i]!=0) printed=true;
                if(!printed)
                    printf("%d ---- none\n",jy);
                else 
                {
                    printf("%d (%d): ",jy,jyy[alen+1]);
                    for(int i=1;i<=alen;i++)
                    {
                        for(int j=1;j<=jyy[i];j++)
                        {
                            if(i==alen&&j==jyy[i])printf("%d",a[i]);
                            else printf("%d ",a[i]);
                        }
                    }
                    printf("\n");
                }
            }
        }
    if(scanf("%d",&a[1])!=EOF) goto start;//循环回前面。
} 