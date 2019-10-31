#include <iostream>
#include <string>
using namespace std;
const int MAXN = 1000010;

int nex1[MAXN];

void dopattern(string pat) {
	nex1[0] = -1;
	int k = -1, j = 0;
	int patlen = pat.size();
	while (j<=patlen - 1) {
		if (k == -1 || pat[j] == pat[k]) {
			++k; ++j;
			//if (pat[j] != pat[k])nex1[j] = k;
			//else nex1[j] = nex1[k];
            nex1[j]=k;
		}
		else {
			k = nex1[k];
		}
	}
}

int search(string str, string pattern) {
	dopattern(pattern);
	int i = 0, j = 0;
	int res = 0;
	int strlen = str.size();
	int patlen = pattern.size();
	while (i < strlen && j < patlen) {
		if (j == -1 || str[i] == pattern[j]) {
			i++; j++;
		}
		else {
			j = nex1[j];
		}
		if (j == patlen) {
			res++;
            j=0;
		}
	}
	return res;
}   



int main() {
    ios::sync_with_stdio(false);
    string inp;
    while(cin>>inp){
        if(inp==".")break;
        dopattern(inp);
        //for(int i=0;i<=inp.size();i++){
        //    cout<<nex1[i]<<" ";
        //}
        //cout<<endl;
        int cyc=inp.size()-nex1[inp.size()];
        if(inp.size()%cyc==0){
            cout<<inp.size()/cyc<<endl;
        }else{
            cout<<1<<endl;
        }
    }

    //while (1);
    return 0;
}
