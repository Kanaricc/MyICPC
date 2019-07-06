#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=100;

int game[MAXN][MAXN];
int take[MAXN][MAXN];
int tgame[MAXN][MAXN];
int n,m;
void doit(int i,int j){
    tgame[i][j]^=1;
    if(i-1>=1)tgame[i-1][j]^=1;
    if(i+1<=n)tgame[i+1][j]^=1;
    if(j-1>=1)tgame[i][j-1]^=1;
    if(j+1<=m)tgame[i][j+1]^=1;
}
int generate(){
    int countnum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            tgame[i][j]=game[i][j];
        }
    }
    for(int j=1;j<=m;j++){
        if(take[1][j]){
            doit(1,j);
            countnum++;
        }
    }
    //from line 2
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(tgame[i-1][j]){
                take[i][j]=1;
                countnum++;
                doit(i,j);
            }
        }
    }
    //check whether problem has been solved.
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(tgame[i][j]==1)return 0x7f7f7f7f;
        }
    }
    return countnum;
}
string getans(){
    string res="";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            res+=take[i][j]+'0';
        }
    }
    //reverse(res.begin(),res.end());
    return res;
}


vector<string> ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>game[i][j];
        }
    }
    int curc=0x7f7f7f7f;
    for(int i=0;i<(1<<m);i++){
        memset(take,0,sizeof(take));
        for(int j=0;j<m;j++){
            if((i>>j)&1)take[1][j+1]=1;
        }

        int c=generate();
        //if(c<0x7f7f7f7f)cout<<getans()<<" "<<c<<endl;
        if(c<curc){
            ans.clear();
            string curans=getans();
            curc=c;
            ans.push_back(curans);
        }
    }
    sort(ans.begin(),ans.end());
    if(ans.empty()){
        cout<<"IMPOSSIBLE"<<endl;
    }else{
        //reverse(ans[0].begin(),ans[0].end());
        for(int i=0;i<ans[0].size();i++){
            if(i!=0 && i%m==0)cout<<endl;
            cout<<ans[0][i]<<" ";
        }
    }


    return 0;
}
