#include <iostream>
#include <string>
using namespace std;

string trim(string &str) {
	//remove suffix and prefix 0
	int ptrs = 0, ptre = str.size() - 1;
	while (str[ptrs] == '0')ptrs++;
	if (str.find('.') != string::npos)
		while (str[ptre] == '0')ptre--;

	//remove suffix .
	if (str[ptre] == '.')ptre--;

	str = str.substr(ptrs, ptre - ptrs+1);
	return str;
}
int main() {
	string inp;
	cin >> inp;
	trim(inp);
	if (inp == "") {
		cout << 0 << endl;
	}
	else if (inp.find('.') == string::npos) {
		int b = inp.size() - 1;
		if (b == 0)cout << inp << endl;
		else {
			//100000000
			if (trim(inp.substr(1)) == "")cout << inp[0] << 'E' << b << endl;
			else {
				//123123213000000
				int last = inp.size()-1;
				while (inp[last] == '0')last--;
				cout << inp[0] << '.' << inp.substr(1,last) << 'E' << b << endl;
			}
		}
	}
	else if (inp.find('.') == 0) {
		//.000001
		//.0000001123123
		int first = 1;
		while (inp[first] == '0')first++;
		//.000001
		if (first == inp.size() - 1) {
			cout << inp[first] << 'E' << -first << endl;
		}
		else {
			//.00000123123
			cout << inp[first] << '.' << inp.substr(first + 1) << 'E' << -first << endl;
		}
	}
	else {
		int pos = inp.find('.');
		if (pos - 1 == 0) {
			cout << inp[0] << '.' << inp.substr(1, pos - 1) << inp.substr(pos + 1) << endl;
		}
		else {
			cout << inp[0] << '.' << inp.substr(1, pos - 1) << inp.substr(pos + 1) << 'E' << pos - 1 << endl;
		}
	}

	//while (1);
	return 0;
}