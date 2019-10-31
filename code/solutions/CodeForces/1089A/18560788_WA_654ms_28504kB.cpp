#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool vis[6][6][201][201];
bool dp[6][6][201][201];
struct Sol{
    int a,b;
    Sol(){}
    Sol(int a,int b):a(a),b(b){}
};

vector<Sol> solution[6][6][201][201];
//win match,failed match,win score,failed score

void join_sol(vector<Sol> &src,vector<Sol> &dest){
    for(int i=0;i<src.size();i++){
        dest.push_back(src[i]);
    }
}
bool dfs(int wm,int fm,int ws,int fs){
    if(vis[wm][fm][ws][fs] || dp[wm][fm][ws][fs])return dp[wm][fm][ws][fs];
    int winscore=(wm+fm)==5?15:25;
    vis[wm][fm][ws][fs]=1;
    //one reached winscore
    //win
    //TODO: if ws-winscore>=0 fs-ofs>=0
    for(int ofs=0;ofs<=winscore-2;ofs++){
        if(wm-1<0 || ws-winscore<0 || fs-ofs<0)break;
        if(dfs(wm-1,fm,ws-winscore,fs-ofs)){
            dp[wm][fm][ws][fs]=1;
            if(solution[wm][fm][ws][fs].size()==0){
                join_sol(solution[wm-1][fm][ws-winscore][fs-ofs],solution[wm][fm][ws][fs]);
                solution[wm][fm][ws][fs].push_back(Sol(winscore,ofs));
            }
        }
    }
    //fail
    //TODO: if above
    for(int ows=0;ows<=winscore-2;ows++){
        if(fm-1<0 || ws-ows<0 || fs-winscore<0)break;
        if(dfs(wm,fm-1,ws-ows,fs-winscore)){
            dp[wm][fm][ws][fs]=1;
            if(solution[wm][fm][ws][fs].size()==0){

                join_sol(solution[wm][fm-1][ws-ows][fs-winscore],solution[wm][fm][ws][fs]);
                solution[wm][fm][ws][fs].push_back(Sol(ows,winscore));
            }
        }
    }
    //up than winscore
    //win
    //TODO: if above
    for(int ows=winscore+1;ows<=ws;ows++){
        if(wm-1<0 || ws-ows<0 || fs-(ows-2)<0)break;
        if(dfs(wm-1,fm,ws-ows,fs-(ows-2))){
            dp[wm][fm][ws][fs]=1;
            if(solution[wm][fm][ws][fs].size()==0){

                join_sol(solution[wm-1][fm][ws-ows][fs-(ows-2)],solution[wm][fm][ws][fs]);
                solution[wm][fm][ws][fs].push_back(Sol(ows,ows-2));
            }
        }
    }
    //fail
    //TODO: if above
    for(int ofs=winscore+1;ofs<=fs;ofs++){
        if(fm-1<0 || ws-(ofs-2)<0 || fs-ofs<0)break;
        if(dfs(wm,fm-1,ws-(ofs-2),fs-ofs)){
            dp[wm][fm][ws][fs]=1;
            if(solution[wm][fm][ws][fs].size()==0){

                join_sol(solution[wm][fm-1][ws-(ofs-2)][fs-ofs],solution[wm][fm][ws][fs]);
                solution[wm][fm][ws][fs].push_back(Sol(ofs-2,ofs));
            }
        }
    }
}

void init_dp(){
    for(int fs=0;fs<=23;fs++){
        dp[1][0][25][fs]=1;
        solution[1][0][25][fs].push_back(Sol(25,fs));

        dp[0][1][fs][25]=1;
        solution[0][1][fs][25].push_back(Sol(fs,25));
    }
}
void print_sol(int wm,int fm,int ws,int fs){
    for(int i=0;i<solution[wm][fm][ws][fs].size();i++){
        Sol &sol=solution[wm][fm][ws][fs][i];
        cout<<sol.a<<":"<<sol.b<<" ";
    }
    cout<<endl;
}
int main(){
    init_dp();
    for(int i=0;i<=5;i++){
        for(int j=0;j<=5;j++){
            for(int ws=0;ws<=200;ws++){
                for(int fs=0;fs<=200;fs++){
                    if(i+j>5)continue;
                    dfs(i,j,ws,fs);
                }
            }
        }
    }
    int len;cin>>len;
    while(len--){
        int a,b;cin>>a>>b;
        if(dp[3][0][a][b]){
            cout<<"3:0"<<endl;
            print_sol(3,0,a,b);
        }else if(dp[3][1][a][b]){
            cout<<"3:1"<<endl;
            print_sol(3,1,a,b);
        }else if(dp[3][2][a][b]){
            cout<<"3:2"<<endl;
            print_sol(3,2,a,b);
        }else if(dp[1][3][a][b]){
            cout<<"1:3"<<endl;
            print_sol(1,3,a,b);
        }else if(dp[0][3][a][b]){
            cout<<"0:3"<<endl;
            print_sol(0,3,a,b);
        }else{
            cout<<"Impossible"<<endl;
        }
    }


    return 0;
}

