#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/string-to-integer-atoi

	Input:
	"-4193 witsign words"

	Output:
	-4193

	Input:
	"        -4193 050304"
	Output:
	-4193
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string str;
	getline(cin, str);
	string s = "";
	for (long long i = 1; i < str.length() - 1; i++) {
		string g(1, str[i]);
		s += g;
	}

	// Method 1:
	// We will find first character that is not space. If that is not a number print 0 else traverse till the numbers continue and multiple the answer by 10 and add the number to it. Now if space or other character comes break the loop and the remaining is answer. If the answer if greater than max/min limit print max/min limit.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long ans = 0;
	long long sign = 1;
	bool flag = true;
	long long i = s.find_first_not_of(' ');
	if (s[i] == '-' || s[i] == '+') {
		sign = (s[i++] == '-') ? -1 : 1;
	}
	while ('0' <= s[i] && s[i] <= '9') {
		ans = ans * 10 + (s[i++] - '0');
		if (ans * sign >= LLONG_MAX) {
			flag = false;
			cout << LLONG_MAX << endl;
			break;
		}
		if (ans * sign <= LLONG_MIN) {
			flag = false;
			cout << LLONG_MIN << endl;
			break;
		}
	}
	if (flag) {
		cout << ans * sign << endl;
	}
	return 0;
}