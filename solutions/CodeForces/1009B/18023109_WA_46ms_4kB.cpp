#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;
const int MAXN=500010;

void print(int one,int two,int zero){
	for(int k=0;k<zero;k++)cout<<0;
	for(int k=0;k<one;k++)cout<<1;
	for(int k=0;k<two;k++)cout<<2;
}
string inp;
int main(){
	cin>>inp;
	int ptr=0,len=inp.size();
	int haszero=0,hastwo=0,hasone=0;
	while(ptr<len){
		haszero=hastwo=hasone=0;
		for(;ptr<len;ptr++){
			if(inp[ptr]=='0'){
				if(hastwo){
					print(hasone,hastwo,haszero);
					break;
				}
				haszero++;
			}
			if(inp[ptr]=='2'){
				if(haszero){
					print(hasone,hastwo,haszero);
					break;
				}
				hastwo++;
			}
			if(inp[ptr]=='1')hasone++;
		}
	}
	print(hasone,hastwo,haszero);
	cout<<endl;
	return 0;
}