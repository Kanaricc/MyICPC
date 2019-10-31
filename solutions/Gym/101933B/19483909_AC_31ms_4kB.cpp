#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
using namespace std;
const int MAXN=10;

int main(){
    ios::sync_with_stdio(false);
    int len;cin>>len;
    int cnt=1;
    bool ok=true;
    for(int i=0;i<len;i++){
        string inp;cin>>inp;
        if(inp=="mumble"){
            cnt++;
        }else{
            stringstream ss;
            ss<<inp;
            int res;
            ss>>res;
            if(res!=cnt){
                ok=false;
            }else cnt++;
        }
    }
    if(ok){
        cout<<"makes sense"<<endl;
    }else{
        cout<<"something is fishy"<<endl;
    }

    return 0;
}
