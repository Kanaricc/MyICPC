#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
const int MAPPING[] = { 2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,0,7,7,8,8,8,9,9,9,0 };

int translate(char *str) {
	int len = 0;
	while (str[len] != '\0')len++;
	//translate alphabet
	for (int i = 0; i < len; i++) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			str[i] = MAPPING[str[i] - 'A'] + '0';
		}
	}

	//translate into number
	int number = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == '-')continue;
		number = number * 10 + (str[i] - '0');
	}

	return number;
}

const int MAXL = 100010;
int list[MAXL];
int main() {

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		char inp[10]; scanf("%s", &inp);

		int tmp = translate(inp);
		list[i] = tmp;
	}
	sort(list, list + n);
	bool hasdup = false;
	for (int i = 0; i < n; i++) {
		int c = 1;//count
		int j = i + 1;//the next different phone number
		while (j < n && list[j] == list[i])j++;
		c = j - i;//count it
		if (c > 1) {
			hasdup = true;
			int phone = list[i];
			
			string op;
			for (int j = 1000000; j >= 1; j /= 10) {
				printf("%d", phone / j - phone / (j * 10) * 10);

				if (j == 10000) {
					printf("%c", '-');
				}
			}
			printf(" %d\n", c);
		}
		i = j; i--;
	}
	if (!hasdup) {
		printf("No duplicates.");
	}

	//while (1);
	return 0;
}
