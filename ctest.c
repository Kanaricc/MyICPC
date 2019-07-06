#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10000010

int a[MAXN];
int len;

void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
void printall(){
    for(int i=0;i<len;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void insertsort(){
    for(int i=0;i<len;i++){
        for(int j=i;j>0;j--){
            if(a[j-1]>a[j])swap(&a[j-1],&a[j]);
        }
        printall();
    }
}

void selectsort(){
    for(int i=0;i<len-1;i++){
        int minn=a[i],ptr=i;
        for(int j=i;j<len;j++){
            if(a[j]<minn){
                ptr=j;
                minn=a[j];
            }
        }
        swap(&a[i],&a[ptr]);
        printall();
    }
}
int quicksort(int l,int r){
    //if(l>=r)return;
    int p=a[l];
    int i=l,j=r;
    while(i<j){
        while(i<j && p<a[j])j--;
        if(i<j)swap(&a[i++],&a[j]);
        while(i<j && a[i]<p)i++;
        if(i<j)swap(&a[i],&a[j--]);
    }
    a[i]=p;
    return i;
}
void QUICK_SORT(int l,int r){
    //printall();
    if(l<r){
        int pi=quicksort(l,r);
        if(l<pi-1)QUICK_SORT(l,pi-1);
        if(pi+1<r)QUICK_SORT(pi+1,r);
    }
}

int main(){
    scanf("%d",&len);
    for(int i=0;i<len;i++){
        scanf("%d",&a[i]);
        //a[i]=1;
    }

    //insertsort();
    //selectsort();
    QUICK_SORT(0,len-1);
    printall();
    return 0;
}
