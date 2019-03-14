#include <iostream>
using namespace std;

int main() {
	int kase; cin >> kase;
	while (kase--) {
		int kth, depth;
		cin >> depth >> kth;

		int ans = 1;
		for(int i=0;i<depth-1;i++) {
			if (kth % 2==0) {
				//右子树
				kth /= 2;
				ans = ans * 2 + 1;
			}
			else {
				kth = (kth + 1) / 2;
				ans = ans * 2;
			}
		}
		cout << ans << endl;
	}

	return 0;
}