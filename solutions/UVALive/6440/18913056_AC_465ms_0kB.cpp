#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXK=110;

struct Pa{
    int pri;
    Pa(){}
    Pa(int pri):pri(pri){}
    bool operator<(const Pa &b)const{
        return pri<b.pri;
    }
};
priority_queue<int> pq[MAXK];
int main(){
    int kase;cin>>kase;
    for(int ki=1;ki<=kase;ki++){
        for(int i=0;i<MAXK;i++)while(!pq[i].empty())pq[i].pop();
        cout<<"Case #"<<ki<<":"<<endl;
        int len;cin>>len;
        for(int i=0;i<len;i++){
            char op;cin>>op;
            if(op=='P'){
                int art,base,k;
                cin>>art>>base>>k;
                pq[k].push(base-k*art);
            }else if(op=='A'){
                int time;cin>>time;
                int maxx=0,k=0;
                for(int j=0;j<MAXK;j++){
                    if(pq[j].empty())continue;
                    int tmp=pq[j].top();
                    if(tmp+time*j>=maxx){
                        maxx=tmp+time*j;
                        k=j;
                    }
                }
                pq[k].pop();
                cout<<maxx<<" "<<k<<endl;
            }
        }
    }
    return 0;
}

