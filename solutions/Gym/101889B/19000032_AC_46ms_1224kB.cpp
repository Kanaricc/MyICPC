#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
const int MAXN = 10;

inline bool isyuan(char x) {
	if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u')return true;
	return false;
}
vector<int> pos;
int main() {
	string inp; cin >> inp;
	for (int i = 0; i < inp.size(); i++) {
		if (isyuan(inp[i])) {
			pos.push_back(i);
		}
	}
	int ans = 0;
	if (pos.size() == 0 || pos.size() == inp.size()) {
		ans = 1;
	}
	else if (isyuan(inp[0]) == false) {
		ans = 0;
	}
	else if (pos.size() == 1) {
		ans = inp.size();
	}
	else {
		int mid = pos.size() / 2;
		if (pos.size() % 2 == 0) mid -= 1;
		int s = pos[mid], e = pos[mid + 1];
		ans = e - s;
	}
	cout << ans << endl;

	//while (1);
	return 0;
}