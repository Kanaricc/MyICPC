#include <iostream>
#include <queue>
#include <functional>
#include <string>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int MAXN=1010;

int n,m;
string game[MAXN];
int count=0;
int solve(){
    count++;
    pair<int,int> posp,posf;
    queue<pair<int,int>> fire[2];
    queue<pair<int,int>> people[2];

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(game[i][j]=='J'){
                people[0].push(make_pair(i,j));
                game[i][j]='.';
            }
            if(game[i][j]=='F'){
                fire[0].push(make_pair(i,j));
                game[i][j]='.';
            }
        }
    }

    int tick=0;
    int itime=0;
    const int of[][2]={{-1,0},{1,0},{0,-1},{0,1}};
    while(1){
        itime++;
        if(count==143 && false){
        for(int i=0;i<n;i++){
            cout<<game[i]<<endl;
        }
        cout<<"---------"<<endl;
        }
        while(!fire[tick].empty()){
            pii curf=fire[tick].front();
            fire[tick].pop();
            if(curf.fi<0 || curf.fi>=n || curf.se<0 || curf.se>=m)continue;
            if(game[curf.fi][curf.se]=='F')continue;
            game[curf.fi][curf.se]='F';
            for(int i=0;i<4;i++){
                pii next=make_pair(curf.fi+of[i][0],curf.se+of[i][1]);
                fire[tick^1].push(next);
            }
        }
        while(!people[tick].empty()){
            pii curp=people[tick].front();
            people[tick].pop();
            if(curp.fi<0 || curp.fi>=n || curp.se<0 || curp.se>=m)return itime;
            if(game[curp.fi][curp.se]!='.')continue;
            game[curp.fi][curp.se]='J';
            for(int i=0;i<4;i++){
                pii next=make_pair(curp.fi+of[i][0],curp.se+of[i][1]);
                people[tick^1].push(next);
            }
        }



        tick^=1;
        if(people[tick].empty())return false;
    }
    return false;
}



int main(){
    int kase;cin>>kase;
    while(kase--){
        cin>>n>>m;
        for(int i=0;i<n;i++){
            cin>>game[i];
        }
        int ans=solve();
        if(ans)
            cout<<ans-1<<endl;
        else
            cout<<"IMPOSSIBLE"<<endl;

    }
    return 0;
}

