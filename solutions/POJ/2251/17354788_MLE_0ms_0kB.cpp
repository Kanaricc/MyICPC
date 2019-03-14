#include <iostream>
#include <queue>
using namespace std;
const int MAXN=40;
int L,R,C;

struct v4q{
    int x,y,z;
    int waste;
    v4q(){}
    v4q(int x,int y,int z,int waste):x(x),y(y),z(z),waste(waste){}
};
char game[MAXN][MAXN][MAXN];
int bfs(int x,int y,int z){
    queue<v4q> q;
    q.push(v4q(x,y,z,0));
    while(!q.empty()){
        v4q cur=q.front();
        q.pop();
        int x=cur.x,y=cur.y,z=cur.z;
        if(game[z][x][y]=='E'){
            return cur.waste;
        }
        for(int of=-1;of<=1;of+=2){
            if(x+of>=1 && x+of<=R && game[z][x+of][y]!='#'){
                q.push(v4q(x+of,y,z,cur.waste+1));
            }
            if(y+of>=1 && y+of<=C && game[z][x][y+of]!='#'){
                q.push(v4q(x,y+of,z,cur.waste+1));
            }
            if(z+of>=1 && z+of<=L && game[z+of][x][y]!='#'){
                q.push(v4q(x,y,z+of,cur.waste+1));
            }
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);


    while(cin>>L>>R>>C){
        if(L==0)break;
        int sx,sy,sz;
        for(int z=1;z<=L;z++){
            for(int x=1;x<=R;x++){
                for(int y=1;y<=C;y++){
                    cin>>game[z][x][y];
                    if(game[z][x][y]=='S'){
                        sx=x;sy=y,sz=z;
                    }
                }
            }
        }
        int ans=bfs(sx,sy,sz);
        if(ans!=-1){
            cout<<"Escaped in "<<ans<<" minute(s)."<<endl;
        }else{
            cout<<"Trapped!"<<endl;
        }
    }

    return 0;
}

