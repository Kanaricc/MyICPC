#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace __gnu_pbds;

tree<int,string> t;
//use set? tree<int,null_type> t;
//iterator will also become Key.
//need null_mapped_type if version is lower than 4.4.0
//TAG:
//rb_tree_tag
//splay_tree_tag
//ov_tree_tag
int main(){
    t.begin();
    t.end();
    t.size();
    t.empty();
    t.clear();
    t[1]="orz";
    t[2]="123";
    t.find(1);
    t.lower_bound(1);
    t.upper_bound(1);
    t.erase(2);

    //t.join(other);
    //t.split(key,other);//split all node bigger than key into other
}
    
