#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct Inp{
	char str[60];
	int ct;
};
Inp inps[110];

bool cmp(const Inp &a, const Inp &b) {
	return a.ct < b.ct;
}
int main() {
	int len, n;
	cin >> len >> n;
	for (int i = 0; i < n; i++) {
		scanf("%s", inps[i].str);
	}

	for (int i = 0; i < n; i++) {
		int A = 0, C = 0, G = 0, T = 0;
		int &ct = inps[i].ct;
		for (int j = len - 1; j >= 0; j--) {
			switch (inps[i].str[j]) {
			case 'A':A++; break;
			case 'C':ct += A; C++; break;
			case 'G':ct += A + C; G++; break;
			case 'T':ct += A + C + G; T++; break;
			}
		}
	}
	sort(inps, inps + n, cmp);
	for (int i = 0; i < n; i++) {
		printf("%s\n", inps[i].str);
	}

	//while (1);
	return 0;
}