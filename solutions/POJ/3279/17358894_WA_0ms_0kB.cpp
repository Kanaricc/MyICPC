#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN=16;
int n,m;
int game[MAXN][MAXN];
int remind[MAXN][MAXN];
int original[MAXN][MAXN];

void iput(int x,int y){
    if(x<=0 || x>n || y<=0 || y>m)return;
    game[x][y]^=1;
}

void play(int x,int y){
    iput(x,y);
    remind[x][y]^=1;
    iput(x+1,y);
    iput(x-1,y);
    iput(x,y+1);
    iput(x,y-1);
}
int solve(int ops){
    memset(remind,0,sizeof(remind));
    for(int i=0;i<MAXN;i++)for(int j=0;j<MAXN;j++)game[i][j]=original[i][j];
    //flush ops
    int res=0;
    for(int i=1;i<=m;i++){
        if(ops&1){
            play(1,i);
            res++;
        }
        ops>>=1;
    }

    //generate other operations.
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(game[i-1][j]==1){
                play(i,j);
                res++;
            }
        }
    }

    //check if game has been solved
    bool ok=true;
    for(int j=1;j<=m;j++){
        if(game[n][j]==1){
            ok=false;
            break;
        }
    }
    if(ok)return res;
    else return -1;
}
string c2s(){
    char res[MAXN*MAXN];
    int ptr=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            res[ptr++]=remind[i][j]+'0';
        }
    }
    res[ptr]='\0';
    return string(res);
}
vector<string> solutions;
int minn=0x7f7f7f7f;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>game[i][j];
            original[i][j]=game[i][j];
        }
    }


    for(int ops=0;ops<=(1<<n)-1;ops++){
        int temp=solve(ops);
        if(temp!=-1){
            if(temp<minn){
                minn=temp;
                solutions.clear();
            }
            solutions.push_back(c2s());
        }
    }
    if(minn!=0x7f7f7f7f){
    sort(solutions.begin(),solutions.end());

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<solutions[0][i*m+j]<<" ";
        }
        cout<<endl;
    }
    }else{
        cout<<"IMPOSSIBLE"<<endl;
    }
    return 0;
}
