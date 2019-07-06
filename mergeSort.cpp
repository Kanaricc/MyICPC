#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN=10;

int a[MAXN];
int b[MAXN];
void mergeSort(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    mergeSort(l,mid);
    mergeSort(mid+1,r);
    int i=l,j=mid+1;
    int ptr=l;
    while(i<=mid && j<=r){
        if(a[i]<a[j]){
            b[ptr]=a[i];
            i++;
        }else{
            b[ptr]=a[j];
            j++;
        }
        ptr++;
    }
    while(i<=mid)b[ptr++]=a[i++];
    while(j<=r)b[ptr++]=a[j++];
    for(int i=l;i<=r;i++)a[i]=b[i];
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    mergeSort(0,n-1);
    for(int i=0;i<n;i++)cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
