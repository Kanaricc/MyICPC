/* 需要链式图存储
const int MAXV=10,MAXE=10;
struct Edge{
    int v,n;
}edges[MAXE];
int head[MAXV];

void adde(int u,int v){
    edges[++idx].v=v;
    edges[idx].n=head[u];
    head[u]=idx;
}
*/
namespace BlockDividedTree{
int cnt=0,B,anc[MAXV],stk[MAXV],top=0,id[MAXV];
void dfs(int u,int fa){    
    for(int i=head[u],v,re=top;i;i=edges[i].n)
        if((v=edges[i].v)!=fa){
            dfs(v,u);
            if(top-re>=B){
                for(++cnt;top!=re;--top)id[stk[top]]=cnt;
                anc[cnt]=u;
            }
        }
    stk[++top]=u;
}
void divide(){
    dfs(1,0);
    //cnt块的数量
    //anc每块的根
    //id每个点属于哪个块
    //B  B<=每个块的的大小<=3B
    if(top){
        if(!cnt)anc[++cnt]=1;
        for(;top;--top)id[stk[top]]=cnt;
    }
}
}
