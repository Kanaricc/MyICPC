#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
const int MAXN=5010;

int nlen,clen;
int num[MAXN];
int origin[MAXN];
vector<int> vec[MAXN];
int color[MAXN];
int main(){
	cin>>nlen>>clen;
	for(int i=1;i<=nlen;i++){
		int inp;cin>>inp;
		num[inp]++;
		origin[inp]++;
		vec[inp].push_back(i);
	}

	//循环每种颜色都涂一次。
	
	int penidx=0;
	int xi=1,yi=1;
	bool ok=true;
	while(xi<=MAXN){
		if(num[xi]==0){
			xi++;
			continue;
		}
		for(;xi<MAXN;xi++){
			if(penidx==0 &&clen+(origin[xi]-num[xi])-origin[xi]<(origin[xi]-num[xi])){
				ok=false;
				break;
			}
			if(penidx+num[xi]>=clen){
				num[xi]=num[xi]-(clen-penidx);
				break;
			}
			
			penidx+=num[xi];
		}
		if(!ok)break;
		penidx=0;
	}
	if(ok){
		cout<<"YES"<<endl;
		//开始涂色
		penidx=1;
		for(int i=0;i<MAXN;i++){
			for(int j=0;j<vec[i].size();j++){
				color[vec[i][j]]=penidx;
				penidx++;
				if(penidx>clen)penidx=1;
			}
		}
		for(int i=1;i<=nlen;i++)cout<<color[i]<<" ";
		cout<<endl;

	}else{
		cout<<"NO"<<endl;
	}
	return 0;
}