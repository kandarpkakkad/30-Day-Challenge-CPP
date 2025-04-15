#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

	Input:
	mbadm

	Output:
	2
	2
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	long long N = s.length();

	// Method 1:
	// We use 2D DP array to store the values of needed characters till length i for string to become palindrome.
	// Let's imagine matching the characters of the string like a palindrome, from the begining and the end with 2 pointers i and j.
	// We may encounter 2 scenarios:
	// 1. The character at i matches character at j.
	// 2. The characters don't match each other
	// In case of 1 we just increase the pointer i and decrease the pointer j, i++ and j-- respectively.
	// In the second case we have 2 options:
	// 1. Insert one character at j to match the character at i.
	// Or
	// 2. Insert one character at i to match the character at j.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	long long dp[N][N] = {};
	for (long long i = N - 1; i >= 0; i--) {
		for (long long j = i; j < N; j++) {
			if (i == j) {
				dp[i][j] = 0;
				// cout << i << "  --  " << j << " -- " << dp[i][j] << endl;
				continue;
			}
			if (s[i] == s[j]) {
				dp[i][j] = dp[i + 1][j - 1];
			}
			else {
				dp[i][j] = min(1 + dp[i + 1][j], 1 + dp[i][j - 1]);
			}
			// cout << i << "  --  " << j << " -- " << dp[i][j] << endl;
		}
	}
	cout << dp[0][N - 1] << endl;

	// Method 2:
	// We are doing the same thing as above but we will use O(n) space now.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	vector<long long> memo_table(N, 0);
	long long prev, temp;
	for (long long i = N - 2; i >= 0; i--) {
		prev = 0;
		for (long long j = i; j < N; j++) {
			temp = memo_table[j];
			memo_table[j] = s[i] == s[j] ? prev : 1 + min(memo_table[j], memo_table[j - 1]);
			prev = temp;
		}
	}
	cout << memo_table[N - 1] << endl;
	return 0;
}