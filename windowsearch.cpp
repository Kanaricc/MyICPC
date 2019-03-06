#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;
typedef long long ll;
struct HashS{
    ll current;
    int base;
    int k;
    HashS(int k,int HASHLEN):k(k){
        base=1;
        current=0;
        for(int i=0;i<HASHLEN-1;i++)base=base*k;
    }
    HashS(){}

    void slide(char in,char out='\0'){
        current=current-out*base;
        current*=k;
        current+=in;
    }
};

struct HashSearch{
    string pattern,str;
    HashS sp,ss;
    int HASHLEN;
    HashSearch(string pattern,string str):pattern(pattern),str(str){
        HASHLEN=pattern.size();
        sp=HashS(256,HASHLEN);
        ss=HashS(256,HASHLEN);
        for(int i=0;i<pattern.size();i++)sp.slide(pattern[i]);
    }
    vector<int> search(){
        vector<int> res;
        for(int i=0;i<str.size();i++){
            char out='\0';
            if(i-HASHLEN>=0)out=str[i-HASHLEN];
            ss.slide(str[i],out);
            if(i-HASHLEN+1<0)continue;
            if(ss.current==sp.current)res.push_back(i-HASHLEN+1);
        }
        return res;
    }
};


int main(){
    string inp;
    string pattern;
    cin>>inp>>pattern;
    HashSearch hs(pattern,inp);
    vector<int> ans=hs.search();
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;

    return 0;
}
