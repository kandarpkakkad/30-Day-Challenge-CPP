#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/coin-change

	Input:
	3 11
	1 2 5

	Output:
	3
	3
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, amt;
	cin >> N >> amt;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// To count the total number of solutions, we can divide all set solutions into two sets.
	// 		1) Solutions that do not contain ith coin.
	// 		2) Solutions that contain at least one ith coin.
	// Time Complexity: O(n*amt)
	// Space Complexity: O(amt)
	long long dp[amt + 1];
	for (long long i = 0; i < amt + 1; i++) {
		dp[i] = amt + 1;
	}
	dp[0] = 0;
	for (long long i = 0; i < N; i++) {
		for (long long j = arr[i]; j < amt + 1; j++) {
			dp[j] = min(dp[j], dp[j - arr[i]] + 1);
		}
	}
	if (dp[amt] > amt) {
		cout << -1 << endl;
	}
	else {
		cout << dp[amt] << endl;
	}

	// Method 2:
	// The same thing is done here except for every coin we will now be checking on every amount.
	// Time Complexity: O(n*amt)
	// Space Complexity: O(amt)
	for (long long i = 0; i < amt + 1; i++) {
		dp[i] = amt + 1;
	}
	dp[0] = 0;
	for (long long i = 1; i < amt + 1; i++) {
		for (long long j = 0; j < N; j++) {
			if (arr[j] <= i) {
				dp[i] = min(dp[i], dp[i - arr[j]] + 1);
			}
		}
	}
	if (dp[amt] > amt) {
		cout << -1 << endl;
	}
	else {
		cout << dp[amt] << endl;
	}
	return 0;
}