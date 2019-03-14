#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;
const int MAXN=500010;

string inp;
string suf;
int main(){
	cin>>inp;
	int len=inp.size();
	int zero=0,one=0;
	bool hastwo=false;
	for(int i=0;i<len;i++){
		if(inp[i]=='1')one++;
		if(inp[i]=='0'){
			if(!hastwo)zero++;
			else suf+='0';
		}
		if(inp[i]=='2'){
			suf+='2';
			hastwo=1;
		}
	}
	for(int k=0;k<zero;k++)cout<<'0';
	for(int k=0;k<one;k++)cout<<'1';
	cout<<suf<<endl;
	return 0;
}