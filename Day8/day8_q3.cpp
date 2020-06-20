#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/coin-change/

	Input:
	3 11
	1 2 5

	Output:
	3
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// Coin Change DP vector, where dp[i] meadn the solution of amount 'i'. We initialize each element of dp vector to -1 and then for each coin value c:
	// if i - c < 0, do nothing
	// if i - c >= 0 and dp[i - c] != 1, means there is solution of amount 'i - c', dp[i] = min(dp[i], dp[i - c] + 1)
	// Time Complexity: O(n * k)
	// Space Complexit: O(k)
	vector<long long> dp(k + 1, -1);
	dp[0] = 0;
	for (long long i = 1; i <= k; i++) {
		for (long long j = 0; j < N; j++) {
			if (i - arr[j] >= 0 && dp[i - arr[j]] != -1) {
				if (dp[i] > 0) {
					dp[i] = min(dp[i], dp[i - arr[j]] + 1);
				}
				else {
					dp[i] = dp[i - arr[j]] + 1;
				}
			}
		}
	}
	cout << dp[k] << endl;
	return 0;
}