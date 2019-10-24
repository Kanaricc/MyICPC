#include <ctime>
#include <iostream>
#include <random>

using namespace std;

int main() {
  mt19937 myrand(time(0));
  cout << myrand() << endl;
  return 0;
}