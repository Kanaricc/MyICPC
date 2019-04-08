#include <iostream>
using namespace std;
double CouponPrice(double);

double ConponPrice(double x)
{
    int c=x/1000;
    switch(c)
    {
    case 0:
        if(x>0)
        {x=x;
        }
        else x=0;
        break;
    case 1:
        x=0.95*x;
        break;
    case 2:
        x=0.9*x;
        break;
    case 3:
        x=0.85*x;
        break;
    case 4:
        x=0.85*x;
        break;
    case 5:case 6:case 7:case 8:case 9:
        x=0.8*x;
        break;
    case 10:
        if(x>10000)
        {
            x=0;
        }
        else x=8000;
        break;
    default:
        x=0;

    }
    return x;
}
int main()
{
    cout << "enter the price:" ;
    double x;
    cin>>x;
    cout<<"the coupon price is:"<<ConponPrice(x);

    return 0;
}
