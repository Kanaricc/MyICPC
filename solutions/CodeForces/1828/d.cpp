#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
using ll = long long;
using pii=pair<int,int>;
constexpr int XN = 5010;

int n;
int a[XN];
int a_sorted[XN];

int main() {
    ios::sync_with_stdio(false);

    int kase;
    cin >> kase;
    while (kase--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        int ans=0;
        for(int l=0;l<n;l++){
            set<int> nums;
            vector<int> div;
            int res=0;
            for(int r=l;r<n;r++){
                if(div.empty()){
                    nums.insert(a[r]);
                    div.push_back(0);
                }else{
                    int to=nums.lower_bound(a[r]);
                    int to=*(--lower_bound(nums.begin(),nums.end(),a[r]));
                    int ptr=r;
                    while(!div.empty() && *div.rbegin()>=num){
                        res-=ptr-*div.rbegin();
                        ptr=*div.rbegin()-1;
                        div.erase(--div.end());
                    }
                    int idx=lower_bound(div.begin(),div.end(),a[r])-div.begin();
                    res+=r-idx;
                    div.push_back(idx);

                    ans+=res;
                }

                cout<<l<<" "<<r<<": ";
                for(auto x:div){
                    cout<<x<<" ";
                }
                cout<<endl;
            }
        }

        cout<<ans<<endl;
    }

    return 0;
}