#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include <regex>
using namespace std;
const int MAXN=200;

int square,len;
struct Ro{
    string name;
    int price,spd,tim,rec;
    int cir;
}ro[MAXN];
void getinput(){
    cin>>square>>len;
    cin.ignore();
    for(int i=0;i<len;i++){
        string inp;getline(cin,inp);
        int ptr=0;
        while(inp[ptr]!=',')ro[i].name+=inp[ptr],ptr++;
        ptr++;
        while(inp[ptr]!=',')ro[i].price=ro[i].price*10+(inp[ptr]-'0'),ptr++;
        ptr++;
        while(inp[ptr]!=',')ro[i].spd=ro[i].spd*10+(inp[ptr]-'0'),ptr++;
        ptr++;
        while(inp[ptr]!=',')ro[i].tim=ro[i].tim*10+(inp[ptr]-'0'),ptr++;
        ptr++;
        while(ptr<inp.size())ro[i].rec=ro[i].rec*10+(inp[ptr]-'0'),ptr++;
    }
}

int main(){
    ios::sync_with_stdio(false);
    getinput();
    vector<string> ans;
    int minp=0x7f7f7f7f7f;
    for(int i=0;i<len;i++){
        //cout<<ro[i].spd<<" "<<ro[i].spd<<" "<<ro[i].tim<<" ")<<ro[i].rec<<endl;
        //cout<<(double)square/(ro[i].spd*ro[i].tim)*(ro[i].tim+ro[i].rec)<<endl;
        if((double)square/(ro[i].spd*ro[i].tim)*(ro[i].tim+ro[i].rec)<=10080){
            if(ro[i].price<minp){
                minp=ro[i].price;
                ans.clear();
                ans.push_back(ro[i].name);
            }else if(ro[i].price==minp){
                ans.push_back(ro[i].name);
            }
        }
    }
    if(!ans.empty()){
        for(int i=0;i<ans.size();i++){
            cout<<ans[i]<<endl;
        }
    }else{
        cout<<"no such mower"<<endl;
    }
    
    return 0;
}
