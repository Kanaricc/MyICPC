#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define PI 3.14159265358979323846
int n;
double inr;
int main(){
	cin>>n>>inr;
	double theta=(double)PI*2/n;
	theta/=2.0;
	cout<<fixed<<setprecision(7)<<inr*sin(theta)/ (1-sin(theta))<<endl;

	return 0;
}