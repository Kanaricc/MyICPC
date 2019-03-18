#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(){
    string inp;
    getline(cin,inp);
    stringstream ss;
    ss<<inp;
    string a;
    ss>>a;
    cout<<a<<endl;
    return 0;
}
    