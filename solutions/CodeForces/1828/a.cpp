#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);

  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cout << i * 2 << " ";
    }
    cout << endl;
  }
  return 0;
}
