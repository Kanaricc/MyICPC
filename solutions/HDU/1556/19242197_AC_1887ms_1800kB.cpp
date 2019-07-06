#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
const int MAXN=100010;

int game[MAXN];

int main(){
    int n;
    while(cin>>n){
        if(n==0)break;
        memset(game,0,sizeof(game));
        int maxx=0;
        for(int i=0;i<n;i++){
            int a,b;cin>>a>>b;
            game[a]++;
            game[b+1]--;
        }
        for(int i=1;i<=n;i++){
            game[i]+=game[i-1];
        }
        for(int i=1;i<n;i++){
            cout<<game[i]<<" ";
        }
        cout<<game[n]<<endl;
    }

    return 0;
}
