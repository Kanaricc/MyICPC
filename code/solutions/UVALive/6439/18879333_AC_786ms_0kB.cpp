#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;


int main(){
    int kase;cin>>kase;
    for(int ki=1;ki<=kase;ki++){
        string inp;cin>>inp;
        int lptr=0,rptr=inp.size();
        int end=rptr;
        int ans=0;
        while(1){
            rptr--;
            if(rptr<lptr)break;
            while(rptr>=lptr && inp[rptr]!=inp[lptr])rptr--;
            //check
            bool ok=true;
            for(int i=0;i<end-rptr;i++){
                if(inp[lptr+i]!=inp[rptr+i]){
                    ok=false;
                    break;
                }
            }
            if(ok){
                lptr+=end-rptr;
                end=rptr;
                if(lptr>end)ans++;
                else ans+=2;
            }else{
                //nothing
            }
        }
        cout<<"Case #"<<ki<<": "<<ans<<endl;
    }

    return 0;
}
