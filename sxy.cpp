#include <iostream>
using namespace std;

int a[5][4];

int average(int (*p)[4]){
    for(int j=0;j<4;j++){
        int sum=0;
        for(int i=1;i<4;i++){
            sum+=*(*(p+i)+j);
        }
        int avg=sum/3;
        *(*(p+4)+j)=avg;
    }
}

int main(){
    a[1][0]=5;
    a[2][0]=10;
    a[3][0]=15;
    average(a);
    cout<<a[4][0]<<endl;

    return 0;

}