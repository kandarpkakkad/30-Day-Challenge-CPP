#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/edit-distance/

	Input:
	intention
	execution

	Output:
	5
	5
	5
*/

long long edit_dist(string a, string b, long long N, long long M) {
	if (M == 0) {
		return N;
	}
	if (N == 0) {
		return M;
	}
	if (a[N - 1] == b[M - 1]) {
		return edit_dist(a, b, N - 1, M - 1);
	}
	return 1 + min(edit_dist(a, b, N, M - 1), min(edit_dist(a, b, N - 1, M), edit_dist(a, b, N - 1, M - 1)));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s1, s2;
	cin >> s1 >> s2;
	long long N = s1.size();
	long long M = s2.size();

	// Method 1:
	// The idea is process all characters one by one staring from either from left or right sides of both strings. Let us traverse from right corner, there are two possibilities for every pair of character being traversed.
	// If last characters of two strings are same, nothing much to do. Ignore last characters and get count for remaining strings. So we recur for lengths m-1 and n-1.
	// Else (If last characters are not same), we consider all operations on ‘str1’, consider all three operations on last character of first string, recursively compute minimum cost for all three operations and take minimum of three values.
	// 		Insert: Recur for m and n-1
	// 		Remove: Recur for m-1 and n
	// 		Replace: Recur for m-1 and n-1
	// Time Complexity: O(3^m)
	// Space Complexity: O(3^m) (recursive stack);
	cout << edit_dist(s1, s2, N, M) << endl;

	// Method 2:
	// We will continue with the same procedure but this time with iterative method and 2D DP. The time complextiy decreases.
	// Time Complexity: O(n*m)
	// Space Complexity: O(n*m)
	long long dp[N + 1][M + 1];
	for (long long i = 0; i <= N; i++) {
		for (long long j = 0; j <= M; j++) {
			if (i == 0) {
				dp[i][j] = j;
			}
			else if (j == 0) {
				dp[i][j] = i;
			}
			else if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
			}
		}
	}
	cout << dp[N][M] << endl;

	// Method 3:
	// In the above method you can see that we are using only 2 rows at a time. So, instead of using N x M matrix we can use 2 x M matrix.
	// Time Complexity: O(n*m)
	// Space Complexity: O(m)
	long long dp2[2][M + 1];
	memset(dp2, 0, sizeof(dp2));
	for (long long i = 0; i <= M; i++) {
		dp2[0][i] = i;
	}
	for (long long i = 1; i <= N; i++) {
		for (long long j = 0; j <= M; j++) {
			if (j == 0) {
				dp2[i % 2][j] = i;
			}
			else if (s1[i - 1] == s2[j - 1]) {
				dp2[i % 2][j] = dp2[(i - 1) % 2][j - 1];
			}
			else {
				dp2[i % 2][j] = 1 + min(dp2[i % 2][j - 1], min(dp2[(i - 1) % 2][j], dp2[(i - 1) % 2][j - 1]));
			}
		}
	}
	cout << dp2[N % 2][M] << endl;
	return 0;
}