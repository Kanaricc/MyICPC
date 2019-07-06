#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
const int MAXN=100010;
const int P=1e9+7;
struct Node{
    char chr;
    int cnt[MAXN];
    bool operator<(const Node &b)const{
        for(int i=MAXN-1;i>=0;i--){
            if(cnt[i]!=b.cnt[i])return cnt[i]<b.cnt[i];
        }
        return false;
    }
}nodes[30];
bool canzero[30];
bool vis[30];
int weight[30];
vector<string> str;

void init(){
    str.clear();
    memset(weight,0,sizeof(weight));
    memset(vis,0,sizeof(vis));
    memset(canzero,1,sizeof(canzero));
    for(int i=0;i<26;i++){
        nodes[i].chr='a'+i;
        memset(nodes[i].cnt,0,sizeof(nodes[i].cnt));
    }
}

inline void countstr(string str){
    reverse(str.begin(),str.end());
    for(int i=0;i<str.size();i++){
        nodes[str[i]-'a'].cnt[i]++;
        vis[str[i]-'a']=1;
    }
}
int main(){
    ios::sync_with_stdio(false);
    int n;
    int kase=0;
    while(cin>>n){
        init();

        for(int i=0;i<n;i++){
            string inp;cin>>inp;
            str.push_back(inp);
            if(inp.size()>1)canzero[inp[0]-'a']=false;
            countstr(inp);
        }
        for(int i=0;i<26;i++){
            for(int j=0;j<MAXN-1;j++){
                nodes[i].cnt[j+1]+=nodes[i].cnt[j]/26;
                nodes[i].cnt[j]%=26;
            }
        }

        sort(nodes,nodes+26);
        int zero=0;
        for(zero=0;zero<26;zero++){
            if(canzero[nodes[zero].chr-'a'])break;
        }

        bool needzero=false;
        if(vis[nodes[0].chr-'a'])needzero=1;

        int curw=25;
        for(int i=25;i>=0;i--){
            if(needzero && i==zero)continue;
            if(!vis[nodes[i].chr-'a'])continue;
            weight[nodes[i].chr-'a']=curw;
            curw--;
        }
        //calculate answer
        ll ans=0;
        for(int i=0;i<n;i++){
            ll one=0;
            for(int j=0;j<str[i].size();j++){
                one=((one*26)%P+weight[str[i][j]-'a'])%P;
            }
            ans=(ans+one)%P;
        }
        cout<<"Case #"<<++kase<<": "<<ans<<endl;
    }

    return 0;
}
