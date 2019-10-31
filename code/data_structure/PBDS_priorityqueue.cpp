#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <functional>
using namespace std;
using namespace __gnu_pbds;
//Time analysis
//pairing_heap_tag: push,join(1),other(logn)
//binary_heap_tag:just push and pop(logn)
//binomial_heap_tag: push(1),other(logn)
//rc_binomial_heap_tag:push(1),other(logn)
//thin_heap_tag:push(1),no join,other(lgn); modify(1) if just increasing key.
//not support means TOO SLOW using it.

//usage
//join-> pairing
__gnu_pbds::priority_queue<int,less<int>,pairing_heap_tag> pq;
int main(){
    pq.clear();
    priority_queue<int>::point_iterator it1=pq.push(1);
    p.modify(it1,9);
    p.erase(it1);
    pq.push(2);
    pq.top();pq.pop();
    pq.empty();
    pq.size();

    //
    auto it=pq.begin();

    pq.join(/*other pq*/);
}


