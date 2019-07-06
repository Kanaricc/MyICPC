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
    int k=0;
    int acc=0;
    int tim=0;
    int ans=0;
    for(int i=0;i<len;i++){
        int day;cin>>day;
        acc+=(day-tim)*k;
        //cout<<"raise to "<<acc<<endl;
        if(acc>=20){
            //cout<<"clean once"<<endl;
            ans++;
            k=0;
            acc=0;
        }
        k++;
        tim=day;
    }
    if(k>0)ans++;
    cout<<ans<<endl;

    return 0;
}
