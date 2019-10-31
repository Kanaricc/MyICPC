#include <iostream>
#include <string>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace std;
using namespace __gnu_pbds;
tree<double,null_type,less<double>,rb_tree_tag,tree_order_statistics_node_update> bbt;
vector<int> a;
double pri=0;
void push(int x){
    bbt.insert((double)x+0.0000001*(pri++));
    a.push_back(x);
}
void pop(){
    bbt.erase(bbt.lower_bound((double)a[a.size()-1]));
    cout<<a[a.size()-1]<<endl;
    a.pop_back();
}
int main(){
    int n;cin>>n;
    while(n--){
        string inp;
        cin>>inp;
        if(inp=="Pop"){
            if(!bbt.empty()){
                pop();
            }else cout<<"Invalid"<<endl;
        }else if(inp=="PeekMedian"){
            if(!bbt.empty()){
                if(bbt.size()%2==0)
                    cout<<(int)*bbt.find_by_order(bbt.size()/2-1)<<endl;
                else cout<<(int)*bbt.find_by_order((bbt.size()+1)/2-1)<<endl;
            }else cout<<"Invalid"<<endl;
        }else if(inp=="Push"){
            int x;cin>>x;
            push(x);
            //cout<<"size="<<bbt.size()<<",smallest"<<bbt.find_by_order(0)->num<<endl;
        }
    }
    return 0;
}

