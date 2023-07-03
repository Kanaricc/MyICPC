#include <algorithm>
#include <iostream>
using namespace std;
constexpr int XN = 200010;

int a[XN];

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int main() {
  ios::sync_with_stdio(false);

  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    int res = a[1] - 1;
    for (int i = 2; i <= n; i++)
      res = gcd(res, abs(a[i] - i));
    cout << res << '\n';
  }
  return 0;
}
