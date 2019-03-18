#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
const int MAXP=10,MAXG=10;

map<string,int> target;
struct P{
    string name;
    int order;
    int g;
    int time,s;
    bool operator<(const P &b)const{
        return order<b.order;
    }
} p[MAXP];
int idx=0;
bool cmp(int a,int b){
    return p[a]<p[b];
}
vector<int> groups[MAXG];
int order[MAXP];
bool done[MAXP];

int main(){
    int plen,glen;cin>>plen>>glen;
    for(int i=1;i<=glen;i++){
        int len;cin>>len;
        for(int j=0;j<len;j++){
            cin>>p[++idx].name;
            p[idx].g=i;
            groups[i].push_back(idx);
            target[p[idx].name]=idx;
        }
    }
    for(int i=0;i<plen;i++){
        string name;
        int s,time;
        cin>>name>>s>>time;
        time=min(time,60);
        if(!target.count(name)){
            p[++idx].name=name;
            p[idx].g=0;
            target[p[idx].name]=idx;
        }
        order[i]=target[name];
        p[order[i]].order=i;
        p[order[i]].time=time;
        p[order[i]].s=s;
    }
    int waste=0;
    int curtime=0;
    for(int i=0;i<plen;i++){
        if(!done[order[i]]){
            if(p[order[i]].g==0){
                cout<<p[order[i]].name<<endl;

                waste=waste+curtime-p[order[i]].s;
                curtime+=p[order[i]].time;

                done[order[i]]=1;
                continue;
            }
            vector<int> group=groups[p[order[i]].g];
            sort(group.begin(),group.end(),cmp);


            int timesum=0;
            for(int j=0;j<group.size();j++){
                if(done[group[j]])continue;
                cout<<p[group[j]].name<<endl;
                waste+=curtime-p[group[j]].s;
                curtime+=p[group[j]].time;
                done[group[j]]=1;
            }
        }
    }
    cout<<waste<<endl;
    cout<<(double)waste/(plen-1)<<endl;
    return 0;
}


