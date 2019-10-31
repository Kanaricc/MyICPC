#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <deque>
using namespace std;
const int MAXN=1010;

int game[MAXN][MAXN];
int maxx[MAXN][MAXN];
int minn[MAXN][MAXN];
int maxxx[MAXN][MAXN];
int minnn[MAXN][MAXN];
int main(){
    int h,w,n;cin>>h>>w>>n;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cin>>game[i][j];
        }
    }

    //单调递减
    deque<int> q;
    deque<int> pos;
    for(int i=1;i<=h;i++){
        q.clear();
        pos.clear();
        for(int j=1;j<=w;j++){
            if(!pos.empty() && j-pos.front()>=n){
                q.pop_front();
                pos.pop_front();
            }
            while(!q.empty() && q.back()<=game[i][j]){
                q.pop_back();
                pos.pop_back();
            }
            q.push_back(game[i][j]);
            pos.push_back(j);
            maxx[i][j]=q.front();
        }
    }

    /*
    cout<<"==="<<endl;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cout<<maxx[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    

    //单调递增
    for(int i=1;i<=h;i++){
        q.clear();
        pos.clear();
        for(int j=1;j<=w;j++){
            if(!pos.empty() && j-pos.front()>=n){
                q.pop_front();
                pos.pop_front();
            }
            while(!q.empty() && q.back()>=game[i][j]){
                q.pop_back();
                pos.pop_back();
            }
            q.push_back(game[i][j]);
            pos.push_back(j);
            minn[i][j]=q.front();
        }
    }
    /*
    cout<<"==="<<endl;
    
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cout<<minn[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    

    for(int j=1;j<=w;j++){
        q.clear();
        pos.clear();
        for(int i=1;i<=h;i++){
            if(!pos.empty() && i-pos.front()>=n){
                q.pop_front();
                pos.pop_front();
            }
            while(!q.empty() && q.back()<=maxx[i][j]){
                q.pop_back();
                pos.pop_back();
            }
            q.push_back(maxx[i][j]);
            pos.push_back(i);
            maxxx[i][j]=q.front();
        }
    }
    /*
    cout<<"==="<<endl;
    
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cout<<maxxx[i][j]<<" ";
        }
        cout<<endl;
    }
    */

    for(int j=1;j<=w;j++){
        q.clear();
        pos.clear();
        for(int i=1;i<=h;i++){
            if(!pos.empty() && i-pos.front()>=n){
                q.pop_front();
                pos.pop_front();
            }
            while(!q.empty() && q.back()>=minn[i][j]){
                q.pop_back();
                pos.pop_back();
            }
            q.push_back(minn[i][j]);
            pos.push_back(i);
            minnn[i][j]=q.front();
        }
    }
    /*
    cout<<"==="<<endl;
    
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cout<<minnn[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    

    int ans=0x7f7f7f7f;
    for(int i=n;i<=h;i++){
        for(int j=n;j<=w;j++){
            ans=min(ans,maxxx[i][j]-minnn[i][j]);
        }
    }
    cout<<ans<<endl;

    return 0;
}
    
