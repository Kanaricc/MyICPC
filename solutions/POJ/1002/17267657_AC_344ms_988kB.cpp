#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int translate(char *inp) {
	int res = 0;
	for (int i = 0, k = 0; k < 7; i++) {
		if ('0' <= inp[i] && inp[i] <= '9') {
			res = res * 10 + (inp[i] - '0');
			k++;
		}
		else if ('A' <= inp[i] && inp[i] < 'Z') {
			int op = 0;
			if (inp[i] > 'Q')op = 1;
			res = res * 10 + ((inp[i] - 'A' - op) / 3 + 2);
			k++;
		}
		//other such as - was thrown.
	}
	return res;
}

int main() {
	int n;
	scanf("%d", &n);
	int phone[100010];

	getchar();
	char inp[256];
	for (int i = 0; i < n; i++) {
		fgets(inp, 256, stdin);
		phone[i] = translate(inp);
	}

	sort(phone, phone + n);
	bool hasup = false;
	for (int i = 0; i < n - 1; i++) {
		int cnt = 1;
		while (phone[i] == phone[i + 1]) {
			cnt++; i++;
		}
		if (cnt > 1) {
			printf("%03d-%04d %d\n", phone[i] / 10000, phone[i] % 10000, cnt);
			hasup = true;
		}
	}
	if (!hasup)printf("No duplicates.\n");

	//while (1);
	return 0;
}