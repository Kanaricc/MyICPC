#include <iostream>
#include <string>
using namespace std;
const int MAXN=1000010;

int nex1[MAXN];

void dopattern(string pat){
    nex1[0]=-1;
    int k=-1,j=0;
    int patlen=pat.size();
    while(j<patlen){
        if(k==-1 || pat[j]==pat[k]){
            ++k;++j;
            if(pat[j]!=pat[k])nex1[j]=k;
            else nex1[j]=nex1[k];
        }else{
            k=nex1[k];
        }
    }
}

int search(string str,string pattern){
    dopattern(pattern);
    int i=0,j=0;
    int strlen=str.size();
    int patlen=pattern.size();
    while(i<strlen && j<patlen){
        if(j==-1 || str[i]==pattern[j]){
            i++;j++;
        }else{
            j=nex1[j];
        }
    }
    if(j==pattern.size())return i-j;
    else return -1;
}



int main(){
    string str;cin>>str;
    int plen;cin>>plen;
    while(plen--){
        string pat;cin>>pat;
        int res=search(str,pat);
        if(res!=-1){
            cout<<str.substr(res)<<endl;
        }else{
            cout<<"Not Found"<<endl;
        }
    }

    return 0;
}

