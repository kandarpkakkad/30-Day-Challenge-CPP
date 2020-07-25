#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/partition-equal-subset-sum

	Input:
	3 50
	60 100 120
	10 20 30

	Output:
	220
	220
	220
*/

long long knapsack_1(long long W, long long wt[], long long val[], long long N) {
	if (N <= 0 || W <= 0) {
		return 0;
	}
	if (wt[N - 1] > W) {
		return knapsack_1(W, wt, val, N - 1);
	}
	else {
		return max(val[N - 1] + knapsack_1(W - wt[N - 1], wt, val, N - 1), knapsack_1(W, wt, val, N - 1));
	}
}

long long knapsack_2(long long W, long long wt[], long long val[], long long i, long long **dp) {
	if (i < 0) {
		return 0;
	}
	if (dp[i][W] != -1) {
		return dp[i][W];
	}
	if (wt[i] > W) {
		dp[i][W] = knapsack_2(W, wt, val, i - 1, dp);
		return dp[i][W];
	}
	else {
		dp[i][W] = max(val[i] + knapsack_2(W - wt[i], wt, val, i - 1, dp), knapsack_2(W - wt[i], wt, val, i - 1, dp));
		return dp[i][W];
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, W;
	cin >> N >> W;
	long long val[N], wt[N];
	for (long long i = 0; i < N; i++) {
		cin >> val[i];
	}
	for (long long i = 0; i < N; i++) {
		cin >> wt[i];
	}

	// Method 1:
	// A simple solution is to consider all subsets of items and calculate the total weight and value of all subsets. Consider the only subsets whose total weight is smaller than W. From all such subsets, pick the maximum value subset.
	// Time Complexity: O(2^n)
	// Space Complexity: O(2^n) (recursive stack)
	cout << knapsack_1(W, wt, val, N) << endl;

	// Method 2:
	// Like other typical Dynamic Programming(DP) problems, recomputations of same subproblems can be avoided by constructing a temporary array K[][] in bottom-up manner.
	// Time Complexity: O(n*w)
	// Space Complexity: O(n*w)
	long long dp[N + 1][W + 1];
	for (long long i = 0; i <= N; i++) {
		for (long long j = 0; j <= W; j++) {
			if (i == 0 || j == 0) {
				dp[i][j] = 0;
			}
			else if (wt[i - 1] <= j) {
				dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	cout << dp[N][W] << endl;

	// Method 3:
	// We will do the recursive approach but with memoization techinique. The recursive steps needs the calculation everytime. So, we will create 2D array to store the output and decrease the number of calculations.
	// Time Complexity: O(n*w)
	// Space Complexity: O(n*w)
	long long **dp2;
	dp2 = new long long *[N];
	for (long long i = 0; i < N; i++) {
		dp2[i] = new long long [W + 1];
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j <= W; j++) {
			dp2[i][j] = -1;
		}
	}
	cout << knapsack_2(W, wt, val, N - 1, dp2) << endl;
	return 0;
}