#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXV=100,MAXE=100;

struct Edge{
    int u,v,cap;
    Edge(){}
    Edge(int u,int v,int cap):u(u),v(v),cap(cap){}
} edges[MAXE];
int idx=0;
vector<int> graph[MAXV];
void adde(int u,int v,int cap){
    graph[u].push_back(idx);
    edges[idx++]=Edge(u,v,cap);
    graph[v].push_back(idx);
    edges[idx++]=Edge(v,u,0);
}

int S,T;
int dis[MAXV];
int current[MAXV];
bool BFS(){
    queue<int> q;
    q.push(S);
    memset(dis,0x3f,sizeof(dis));
    dis[S]=0;
    while(!q.empty()){
        int h=q.front();q.pop();
        for(int ei=0;ei<graph[h].size();ei++){
            Edge &e=edges[graph[h][ei]];
            if(e.cap>0 && dis[e.v]==0x3f3f3f3f){
                dis[e.v]=dis[h]+1;
                q.push(e.v);
            }
        }
    }
    return dis[T]<0x3f3f3f3f;
}
int dinic(int u,int maxflow){
    if(u==T)return maxflow;
    for(int ei=current[u];ei<graph[u].size();ei++){
        current[u]=ei;
        Edge &e=edges[graph[u][ei]];
        if(dis[e.v]==dis[u]+1 && e.cap>0){
            int flow=dinic(e.v,min(maxflow,e.cap));
            if(flow){
                e.cap-=flow;
                edges[graph[u][ei]^1].cap+=flow;
                return flow;
            }
        }
    }
    return 0;
}
int DINIC(){
    int ans=0;
    while(BFS()){
        memset(current,0,sizeof(current));
        int flow;
        while(flow=dinic(S,0x3f3f3f3f))ans+=flow;
    }
    return ans;
}
/*      1    2   3   4
 *  n+1 0    0   0   0
 *  n+2 0    1   1   0
 *  n+3 1    0   1   0
 *  n+4 0    1   0   0
 */

char game[5][5];
int horizon[5][5];
int vertical[5][5];
int tick=10;
int main(){
    int len;
    while(cin>>len){
        if(len==0)break;
        for(int i=0;i<MAXV;i++)graph[i].clear();
        idx=0;
        for(int i=0;i<=4;i++)for(int j=0;j<=4;j++)horizon[i][j]=vertical[i][j]=0;
        tick=10;

        for(int i=1;i<=len;i++){
            for(int j=1;j<=len;j++){
                cin>>game[i][j];
            }
        }
        for(int i=0;i<=len;i++)game[i][0]='X';
        for(int j=0;j<=len;j++)game[0][j]='X';

        for(int i=0;i<=len;i++){
            for(int j=0;j<=len;j++){
                if(game[i][j]!='X')continue;
                while(j<=len && game[i][j]=='X')j++;
                if(j>len)continue;//±ßÔµX
                j--;
                horizon[i][j]=++tick;
            }
        }

        //debug
        /*
           for(int i=0;i<=len;i++){
           for(int j=0;j<=len;j++){
           cout<<horizon[i][j]<<" ";
           }
           cout<<endl;
           }
           */

        for(int j=0;j<=len;j++){
            for(int i=0;i<=len;i++){
                if(game[i][j]!='X')continue;
                while(i<=len && game[i][j]=='X')i++;
                if(i>len)continue;
                i--;
                vertical[i][j]=++tick;
            }
        }
        /*
           for(int i=0;i<=len;i++){
           for(int j=0;j<=len;j++){
           cout<<vertical[i][j]<<" ";
           }
           cout<<endl;
           }
           */
        for(int i=0;i<=len;i++){
            for(int j=0;j<=len;j++){
                if(vertical[i][j]){
                    for(int ii=i+1;ii<=len;ii++){
                        if(vertical[ii][j])break;
                        for(int jj=j-1;jj>=0;jj--){
                            if(horizon[ii][jj] && game[ii][j]!='X'){
                                adde(vertical[i][j],horizon[ii][jj],1);
                                //cout<<"add "<<vertical[i][j]<<"->"<<horizon[ii][jj]<<endl;
                                break;
                            }
                        }
                    }
                }
            }
        }


        S=1,T=2;
        for(int i=0;i<=len;i++){
            for(int j=0;j<=len;j++){
                if(vertical[i][j])adde(S,vertical[i][j],1);
            }
        }
        for(int i=0;i<=len;i++)for(int j=0;j<=len;j++)if(horizon[i][j])adde(horizon[i][j],T,1);

        cout<<DINIC()<<endl;
    }

    return 0;
}


