#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
    string str,f;
    getline(cin,str);
    getline(cin,f);
    int pos=str.find(f);
    if(pos!=string::npos){
        cout<<str.substr(pos,str.size()-pos)<<endl;
    }else{
        cout<<"NULL!"<<endl;
    }

    return 0;
}
