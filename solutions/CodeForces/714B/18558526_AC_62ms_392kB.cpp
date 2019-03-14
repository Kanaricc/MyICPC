#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=100010;

int game[MAXN];
int main(){
    ios::sync_with_stdio(false);
    int len;cin>>len;
    for(int i=0;i<len;i++){
        cin>>game[i];
        }
    sort(game,game+len);
    int *end=unique(game,game+len);
    //1. one group ->
    //2. two group ->
    //3. three group ->
    //4. other...
    /*
    for(int *ptr=game;ptr!=end;ptr++){
        cout<<*ptr<<" ";
    }
    cout<<endl;
    */
    if(end-game==1){
        cout<<"YES"<<endl;
    }else if(end-game==2){
            cout<<"YES"<<endl;
    }else if(end-game==3){
        if(game[2]-game[1]==game[1]-game[0]){
            cout<<"YES"<<endl;
        }else cout<<"NO"<<endl;
    }else {
        cout<<"NO"<<endl;
    }
    return 0;
}
