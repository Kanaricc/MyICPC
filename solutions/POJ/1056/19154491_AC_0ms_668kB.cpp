#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> str;

inline bool comp(string pre,string s){
    for(int i=0;i<pre.size();i++){
        if(pre[i]!=s[i])return false;
    }
    return true;
}
bool check(){
    sort(str.begin(),str.end());
    for(int i=0;i<str.size()-1;i++){
        if(comp(str[i],str[i+1]))return false;
    }
    return true;
}
        
int main(){
    string inp;
    int cnt=0;
    while(cin>>inp){
        if(inp=="9"){
            cnt++;
            if(check()){
                cout<<"Set "<<cnt<<" is immediately decodable"<<endl;
            }else{
                cout<<"Set "<<cnt<<" is not immediately decodable"<<endl;
            }
            str.clear();
            continue;
        }
        str.push_back(inp);
    }

    return 0;
}


