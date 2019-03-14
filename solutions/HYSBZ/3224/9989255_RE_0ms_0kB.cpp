#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 100010;

int data[MAXN];
    int csiz[MAXN];
    int ch[MAXN][2];
    int fa[MAXN];
    int same[MAXN];
    int root;
    int siz;
struct Splay {
    
    Splay(){
        siz=root=0;
        memset(ch,0,sizeof(ch));
        memset(fa,0,sizeof(fa));
        memset(data,0,sizeof(data));
        memset(csiz,0,sizeof(data));
        memset(same,0,sizeof(same));
    }
    int son(int node)
    {
        return ch[fa[node]][0] == node ? 0 : 1;
    }
    void rotate(int node)
    {
        int f = fa[node], ff = fa[f]; // fff=fa[ff](smile)
        int a = son(node), aa = son(f), b = ch[node][!a];

        fa[node] = ff;
        if(ff) {
            ch[ff][aa] = node;
        } else {
            root = node;
        }
        if(b)
            fa[b] = f;
        ch[f][a] = b;
        ch[node][!a] = f;
        fa[f] = node;
        pushup(f);
        pushup(node);
    }
    void splay(int node, int target)
    {
        while(fa[node] != target) {
            int f = fa[node], ff = fa[f];
            if(ff == target) {
                pushdown(ff);
                pushdown(f);
                rotate(node);
            } else {
                pushdown(ff);
                pushdown(f);
                pushdown(node);
                if(son(node) == son(f)) {
                    rotate(f);
                    rotate(node);
                } else {
                    rotate(node);
                    rotate(node);
                }
            }
        }
    }
    void pushup(int node)
    {
        csiz[node]=csiz[ch[node][0]]+csiz[ch[node][1]]+same[node];
    }
    void pushdown(int node){
        
    }
    int find(int x)
    {
        int cur=root;
        while(1){
            if(cur==0){
                //to fit binary search
                if(data[fa[cur]]>x)return -1;
                else return siz+1;
            }
            if(data[cur]==x){
                this->splay(cur,0);
                return cur;
            }
            else if(data[cur]>x)cur=ch[cur][0];
            else if(data[cur]<x)cur=ch[cur][1];
        }
    }
    int dfs(int node,int dest){
        if(ch[node][dest]==0)return node;
        return dfs(ch[node][dest],dest);
    }
    int getb(int node,int x){
        /*
        if(find(x)!=-1){
            return data[dfs(root,1)];
        }else return -1;
        */
        int cur=node,res;
        while(cur){
            if(x<=data[cur])cur=ch[cur][0];
            else{
                res=cur;
                cur=ch[cur][1];
            }
        }
        return res;
    }
    int geta(int node,int x){
        /*
        if(find(x)!=-1){
            return data[dfs(root,0)];
        }
        return -1;
        */
        int cur=node,res;
        while(cur){
            if(x>=data[cur])cur=ch[cur][1];
            else{
                res=cur;
                cur=ch[cur][0];
            }
        }
        return res;
    }
    int getmn(int node){
        int cur=node,res=-1;
        while(cur){
            res=cur;
            cur=ch[cur][0];
        }
        return res;
    }
    
    int getrank(int node,int x){
        if(data[node]==x){
            splay(node,0);
            if(ch[node][0]==0){
                return 1;
            }else{
                return csiz[ch[node][0]]+1;
            }
        }
        if(x<data[node])return getrank(ch[node][0],x);
        else return getrank(ch[node][1],x);
    }
    int getxbyrank(int node,int k){
        int l=ch[node][0];
        if(csiz[l]+1<=k && k<=csiz[l]+same[node])return data[node];
        if(k<csiz[l]+1)return getxbyrank(l,k);
        if(csiz[l]+same[node]<k)return getxbyrank(ch[node][1],k-(csiz[l]+same[node]));
    }
    void remove(int node,int x){
        if(data[node]==x){
            if(same[node]>1){
                same[node]--;csiz[node]--;
            }else{
                splay(node,0);
                int p=getmn(ch[node][1]);
                if(p!=-1){
                    splay(p,node);
                    root=p;fa[p]=0;
                    ch[p][0]=ch[node][0];fa[ch[node][0]]=p;
                    pushup(p);
                }else{
                    root=ch[node][0];fa[ch[node][0]]=0;
                }
            }
            return;
        }
        if(x<data[node]){
            remove(ch[node][0],x);
            pushup(node);
        }else{
            remove(ch[node][1],x);
            pushup(node);
        }
    }
    void addNum(int &node,int x)
    {
        if(node==0){
            node=++siz;
            data[siz]=x;
            csiz[siz]=same[siz]=1;
            return;
        }
        if(x==data[node]){
            same[node]++;csiz[node]++;
            return;
        }
        if(x<data[node]){
            addNum(ch[node][0],x);
            fa[ch[node][0]]=node;
            pushup(node);
        }else{
            addNum(ch[node][1],x);
            fa[ch[node][1]]=node;
            pushup(node);
        }
    }

};
Splay splay;
int main(){
    int k;cin>>k;
    while(k--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            splay.addNum(root,x);
        }else if(op==2){
            splay.remove(root,x);
        }else if(op==3){
            cout<<splay.getrank(root,x)<<endl;
        }else if(op==4){
            cout<<splay.getxbyrank(root,x)<<endl;
        }else if(op==5){
            cout<<data[splay.getb(root,x)]<<endl;
        }else if(op==6){
            cout<<data[splay.geta(root,x)]<<endl;
        }
    }
}