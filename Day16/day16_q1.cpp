#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/

	Input:
	ABCBABCBABCBACBABC
	ABC

	Output:
	Pattern at: 0 to 3
	Pattern at: 4 to 7
	Pattern at: 8 to 11
	Pattern at: 15 to 18
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string str, pat;
	getline(cin, str);
	getline(cin, pat);

	// For a string str[0..n-1], Z array is of same length as string. An element Z[i] of Z array stores length of the longest substring starting from str[i] which is also a prefix of str[0..n-1]. The first entry of Z array is meaningless as complete string is always prefix of itself.
	long long N = str.length();
	long long M = pat.length();
	long long Z[N + M + 1];
	string concat = pat + "$" + str;
	long long len = N + M + 1;
	long long L = 0, R = 0, k;
	// Construction of Z array/ Prefix array
	for (long long i = 1; i < len; i++) {
		if (i > R) {
			// R - L = 0 in starting, so it will start checking from 0'th index. For example, for "ababab" and i = 1, the value of R remains 0 and Z[i] becomes 0. For string "aaaaaa" and i = 1, Z[i] and R become 5
			L = R = i;
			while (R < len && concat[R - L] == concat[R]) {
				R++;
			}
			Z[i] = R - L;
			R--;
		}
		else {
			// k = i-L so k corresponds to number which matches in [L,R] interval
			k = i - L;
			// If Z[k] is less than remaining interval then Z[i] will be equal to Z[k].
			// For example, str = "ababab", i = 3, R = 5 and L = 2
			if (Z[k] < R - i + 1) {
				Z[i] = Z[k];
			}
			// For example str = "aaaaaa" and i = 2, R is 5, L is 0
			else {
				// Else start from R and check manually.
				L = i;
				while (R < len && concat[R - L] == concat[R]) {
					R++;
				}
				Z[i] = R - L;
				R--;
			}
		}
	}
	for (long long i = 0; i < len; i++) {
		if (Z[i] == M) {
			cout << "Pattern at: " << i - M - 1 << " to " << i - 1 << endl;
		}
	}
	return 0;
}