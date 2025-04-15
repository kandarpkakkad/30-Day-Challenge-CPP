#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/palindrome-partitioning-ii/

	Input:
	ababbbabbababa

	Output:
	3
	3
*/

bool is_palin(string s) {
	for (long long i = 0; i < s.length() / 2; i++) {
		if (s[i] != s[s.length() - i - 1]) {
			return false;
		}
	}
	return true;
}

long long min_palin_part(string s, long long start, long long end) {
	if (start >= end || is_palin(s.substr(start, end))) {
		return 0;
	}
	long long ans = LLONG_MAX;
	for (long long i = start; i < end; i++) {
		long long count = 1 + min_palin_part(s, start, i) + min_palin_part(s, i + 1, end);
		ans = min(ans, count);
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	long long N = s.length();

	// Method 1:
	// Calculate and maintain 2 DP states:
	// 		palin[i][j] , which is whether s[i..j] forms a palin
	// 		d[i], which is the minCut for s[i..n-1]
	// Once we comes to a palin[i][j]==true:
	// 		if j==0, the string s[0..i] is a Palin, minCut is 0, d[i]=0;
	// 		else: the current cut num (first cut s[j..i] and then cut the rest
	// 		s[0...j-1]) is 1+d[j-1], compare it to the exisiting minCut num
	// 		d[i], repalce if smaller.
	// d[n - 1] is the answer.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	bool palin[N][N];
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < N; j++) {
			palin[i][j] = false;
		}
	}
	long long dp[N];
	for (long long i = 0; i < N; i++) {
		palin[i][i] = true;
		dp[i] = i;
	}
	for (long long i = 1; i < N; i++) {
		for (long long j = i; j >= 0; j--) {
			if (s[i] == s[j] && (i - j < 2 || palin[i - 1][j + 1] == true)) {
				if (j == 0) {
					dp[i] = 0;
				}
				else {
					palin[i][j] = true;
					dp[i] = min(dp[j - 1] + 1, dp[i]);
				}
			}
		}
	}
	cout << dp[N - 1] << endl;

	// Method 2:
	// We will do the same thing but with recursion.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	cout << min_palin_part(s, 0, N) << endl;
	return 0;
}