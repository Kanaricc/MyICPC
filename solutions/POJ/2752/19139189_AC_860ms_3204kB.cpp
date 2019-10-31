#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int MAXN = 1000010;

int next1[MAXN];
void dopattern(string pat){
    next1[0]=-1;
    int k=-1;
    for(int i=1;i<pat.size();i++){
        while(k>-1 && pat[k+1]!=pat[i]){
            k=next1[k];
        }
        if(pat[k+1]==pat[i]){
            k++;
        }
        next1[i]=k;
    }
}

int kmp(string str,string pat){
    int res=0;
    dopattern(pat);
    int k=-1;
    for(int i=0;i<str.size();i++){
        while(k>-1 && pat[k+1]!=str[i])k=next1[k];
        if(pat[k+1]==str[i])k++;
        if(k==pat.size()-1){
            //position at i-pat.size()+1;
            k=-1;
            i=i-pat.size()+1;
            res++;
        }
    }
    return res;
}

int main(){
    //fvck the former template.
    string pat;
    while(cin>>pat){
        dopattern(pat);
        //for(int i=0;i<pat.size();i++){
        //    cout<<next1[i]<<" ";
        //}
        //cout<<endl;

        vector<int> ans;
        for(int ptr=pat.size()-1;ptr!=-1;ptr=next1[ptr]){
            ans.push_back(ptr+1);
        }
        for(int i=ans.size()-1;i>=0;i--){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }



    return 0;
}
