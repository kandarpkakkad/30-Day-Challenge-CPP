#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/compare-version-numbers/

	Input:
	7.5.2.4
	7.5.3

	Output:
	-1

	Input:
	1.0.01
	1.0.001

	Output:
	0

	Input:
	1.0.1
	1

	Output:
	1
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s1, s2;
	cin >> s1 >> s2;

	// Method 1:
	// Until they are same, we keep on checking. The point of difference will tell the answer. If they are same the answer is 0. This is done by 2 pointer.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long v1 = 0, v2 = 0;
	long long i = 0, j = 0;
	do {
		v1 = 0;
		v2 = 0;
		if (s1[i] == '.') {
			i++;
		}
		if (s2[j] == '.') {
			j++;
		}
		for (; s1[i] != '.' && s1[i] != '\0'; i++) {
			v1 *= 10;
			v1 += (s1[i] - '0');
		}
		for (; s2[j] != '.' && s2[j] != '\0'; j++) {
			v2 *= 10;
			v2 += (s2[j] - '0');
		}
		if (v1 > v2) {
			cout << 1 << endl;
			break;
		}
		else if (v1 < v2) {
			cout << -1 << endl;
			break;
		}
		else if (s1[i] == '\0' && s2[j] == '\0') {
			cout << 0 << endl;
			break;
		}
	} while (s1[i] == '.' || s2[j] == '.');
	return 0;
}