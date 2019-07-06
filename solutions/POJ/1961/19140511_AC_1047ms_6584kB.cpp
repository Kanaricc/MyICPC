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
        while(k>-1 && pat[k+1]!=pat[i])k=next1[k];
        if(pat[k+1]==pat[i])k++;
        next1[i]=k;
    }
}

void doval(string pat){
    //fix -1
    for(int i=1;i<pat.size();i++){
        if(next1[i]==-1)next1[i]=0;
    }
    //for(int i=1;i<pat.size();i++){
    //    if(next1[i]!=-1 && pat[i]==pat[next1[i]])next1[i]=next1[next1[i]];
    //}
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
    for(int k=1;;k++){
        int len;cin>>len;
        if(len==0)break;

        string pat;cin>>pat;
        dopattern(pat);
        //for(int i=0;i<pat.size();i++){
        //    cout<<next1[i]<<" ";
        //}
        //cout<<endl;

        cout<<"Test case #"<<k<<endl;
        for(int i=1;i<pat.size();i++){
            int pei=(i+1)-(next1[i]+1);
            if(pei==0)continue;
            if((i+1)%pei==0 && (i+1)/pei>1){
                cout<<i+1<<" "<<(i+1)/pei<<endl;
            }
        }
        cout<<endl;
    }



    return 0;
}
