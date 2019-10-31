#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
const int MAXN=1010;
int P=10;

int vis[MAXN][MAXN];
string pat;
int patlen;
bool dfs(int pos,int rest,string ans){
    if(pos>=patlen){
        if(rest==0){
            cout<<ans<<endl;
            return true;
        }else return false;
    }
    if(vis[pos][rest])return false;

    if(pat[pos]=='?'){
        for(int i=0;i<=9;i++){
            if(pos==0 && i==0)continue;
            if(dfs(pos+1,(rest*10+i)%P,ans+(char)('0'+i)))return true;
        }
    }else{
        if(dfs(pos+1,(rest*10+pat[pos]-'0')%P,ans+pat[pos]))return true;
    }
    vis[pos][rest]=1;
    return false;
}
int main(){
    cin>>pat>>P;
    patlen=pat.size();
    if(!dfs(0,0,"")){
        cout<<"*"<<endl;
    }
    return 0;
}

