#include <iostream>
#include <string>
#include <cstring>
using namespace std;
const int MAXN = 100;

bool real[MAXN];
string inp[3][3];
int main() {
	int kase; cin >> kase;
	while (kase--) {
		memset(real, 0, sizeof(real));
		for (int i = 0; i < 3; i++) {
			cin >> inp[i][0] >> inp[i][1] >> inp[i][2];
		}
		for (int i = 0; i < 3; i++) {
			string &left = inp[i][0];
			string &right = inp[i][1];
			string &statue = inp[i][2];
			if (statue == "even") {
				for (int i = 0; i < left.size(); i++)real[left[i] - 'A'] = 1;
				for (int j = 0; j < right.size(); j++)real[right[j] - 'A'] = 1;
			}
		}
		char res;
		bool light;
		for (int i = 0; i < 3; i++) {
			string &left = inp[i][0];
			string &right = inp[i][1];
			string &statue = inp[i][2];
			if (statue == "down") {
				for (int j = 0; j < left.size(); j++) {
					if (real[left[j] - 'A'] != 1) {
						res = left[j];
						light = 1;
						break;
					}
				}
				for (int j = 0; j < right.size(); j++) {
					if (real[right[j] - 'A'] != 1) {
						res = right[j];
						light = 0;
						break;
					}
				}
			}
			else if (statue == "up") {
				for (int j = 0; j < left.size(); j++) {
					if (real[left[j] - 'A'] != 1) {
						res = left[j];
						light = 0;
						break;
					}
				}
				for (int j = 0; j < right.size(); j++) {
					if (real[right[j] - 'A'] != 1) {
						res = right[j];
						light = 1;
						break;
					}
				}
			}
		}
		cout << res << " is the counterfeit coin and it is " << (light ? "light" : "heavy") << "." << endl;
	}

	return 0;
}