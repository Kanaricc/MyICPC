#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <algorithm>
#include <regex>
#include <cstdlib>
#include <string>
using namespace std;
const int MAXN=1010;

struct Tree{
    int data[MAXN],idx;
    int lc[MAXN],rc[MAXN];
    int root;
    Tree(){
        root=0;
        idx=0;
        memset(lc,0,sizeof(lc));
        memset(rc,0,sizeof(rc));
        memset(data,0,sizeof(data));
    }
    void addnode(int node,bool left,int x){
        data[++idx]=x;
        if(left)lc[node]=idx;
        else rc[node]=idx;
    }
    void insert(int &node,int x){
        if(!node){
            node=++idx;
            data[idx]=x;
            return;
        }
        if(x<data[node])insert(lc[node],x);
        else insert(rc[node],x);
    }
};

Tree t;

map<int,int> ref;
bool haschild(int u,int x){
    if(t.lc[u]==x || t.rc[u]==x)return true;
    return false;
}
bool haschild_f(int u,int x){
    if(haschild(u,x))return true;
    if(haschild_f(t.lc[u],x))return true;
    if(haschild_f(t.rc[u],x))return true;
    return false;
}
bool haschildren(int u,int x,int y){
    if(hashild(u,x) && haschild(u,y))return true;
    return false;
}
bool haschildren_f(int u,int x,int y){
    if(haschildren(u,x,y))return true;
    if(haschildren_f(t.lc[u],x,y))return true;
    if(haschildren_f(t.rc[u],x,y))return true;
    return false;
}
int getposition(int u,int x){
    return t.rc[u]==x;
}
int getdepth(int u,int x,int depth){
    if(u==x)return depth;
    int d=getdepth(t.lc[u],x,depth+1);
    if(d)return d;
    d=getdepth(t.rc[u],x,depth+1);
    if(d)return d;
    return 0;
}

inline void pres(bool b){
    if(b)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}
void travel(int u){
    if(u==0)return;
    ref[t.data[u]]=u;
    travel(t.lc[u]);
    travel(t.rc[u]);
}
int main(){
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        t.insert(t.root,x);
    }
    /*
    for(int i=1;i<=n;i++){
        cout<<i<<":"<<t.data[i]<<",l"<<t.lc[i]<<",r"<<t.rc[i]<<endl;
    }
    */
    int q;cin>>q;
    cin.ignore();

    regex q_root(R"((\d+) is the root)");
    regex q_siblings(R"((\d+) and (\d+) are siblings)");
    regex q_level(R"((\d+) and (\d+) are on the same level)");
    regex q_parent(R"((\d+) is the parent of (\d+))");
    regex q_left(R"((\d+) is the left child of (\d+))");
    regex q_right(R"((\d+) is the right child of (\d+))");


    while(q--){
        smatch result;
        string inp;
        getline(cin,inp);
        if(regex_match(inp,result,q_root)){
            int x=atoi(result.str(1).c_str());            
        }else if(regex_match(inp,result,q_siblings)){
            int a=atoi(result.str(1).c_str());
            int b=atoi(result.str(2).c_str());
        }else if(regex_match(inp,result,q_level)){
            int a=atoi(result.str(1).c_str());
            int b=atoi(result.str(2).c_str());
        }else if(regex_match(inp,result,q_parent)){
            int a=atoi(result.str(1).c_str());
            int b=atoi(result.str(2).c_str());
        }else if(regex_match(inp,result,q_left)){
            int a=atoi(result.str(1).c_str());
            int b=atoi(result.str(2).c_str());
        }else if(regex_match(inp,result,q_right)){
            int a=atoi(result.str(1).c_str());
            int b=atoi(result.str(2).c_str());
        }

    }




    return 0;
}

