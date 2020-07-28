#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/super-egg-drop/

	Input:
	2 10

	Output:
	4
	4
	4
	4
*/

long long egg_drop(long long N, long long k) {
	if (k == 1 || k == 0) {
		return k;
	}
	if (N == 1) {
		return k;
	}
	long long mn = LLONG_MAX, ans;
	for (long long i = 1; i <= k; i++) {
		ans = max(egg_drop(N - 1, i - 1), egg_drop(N, k - i));
		mn = min(ans, mn);
	}
	return mn + 1;
}

long long bin_coeff(long long x, long long n) {
	long long sum = 0, term = 1;
	for (long long i = 1; i <= n; i++) {
		term *= x - i + 1;
		term /= i;
		sum += term;
	}
	return sum;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;

	// Method 1:
	// When we drop an egg from a floor x, there can be two cases (1) The egg breaks (2) The egg doesn’t break.
	// 		1. If the egg breaks after dropping from ‘xth’ floor, then we only need to check for floors lower than ‘x’ with remaining eggs as some floor should exist lower than ‘x’ in which egg would not break; so the problem reduces to x-1 floors and n-1 eggs.
	// 		2. If the egg doesn’t break after dropping from the ‘xth’ floor, then we only need to check for floors higher than ‘x’; so the problem reduces to ‘k-x’ floors and n eggs.
	// Since we need to minimize the number of trials in worst case, we take the maximum of two cases.
	// Time Complexity: O(2^n)
	// Space Complexity: O(2^n) (recursive stack)
	cout << egg_drop(N, k) << endl;

	// Method 2:
	// In this approach, we work on the same idea as described above neglecting the case of calculating the answers to sub-problems again and again.. The approach will be to make a table which will store the results of sub-problems so that to solve a sub-problem, it would only require a look-up from the table which will take constant time.
	// Time Complexity: O(n*k^2)
	// Space Complexity: O(n*k)
	long long dp[N + 1][k + 1];
	long long ans;
	for (long long i = 1; i <= N; i++) {
		dp[i][1] = 1;
		dp[i][0] = 1;
	}
	for (long long i = 1; i <= k; i++) {
		dp[1][i] = i;
	}
	for (long long i = 2; i <= N; i++) {
		for (long long j = 2; j <= k; j++) {
			dp[i][j] = LLONG_MAX;
			for (long long l = 1; l <= j; l++) {
				ans = 1 + max(dp[i - 1][l - 1], dp[i][j - l]);
				dp[i][j] = min(ans, dp[i][j]);
			}
		}
	}
	cout << dp[N][k] << endl;

	// Method 3:
	// Consider this problem in a different way:
	// Let dp[x][n] is the maximum number of floors that can be checked with given n eggs and x moves.
	// Then the equation is:
	// dp[x][n] = dp[x – 1][n – 1] + dp[x – 1][n] + 1
	// which means we take 1 move to a floor,
	// 		1. If the egg breaks, then we can check dp[x – 1][n – 1] floors.
	// 		2. If the egg doesn’t break, then we can check dp[x – 1][n] + 1 floors.
	// Since we need to cover k floors, dp[x][n] >= k.
	// Time Complexity: O(nlog(k))
	// Space Complexity: O(n*k)
	long long dp2[k + 1][N + 1];
	memset(dp2, 0, sizeof(dp2));
	long long i = 0;
	while (dp2[i][N] < k) {
		i++;
		for (long long j = 1; j <= N; j++) {
			dp2[i][j] = dp2[i - 1][j - 1] + dp2[i - 1][j] + 1;
		}
	}
	cout << i << endl;

	// Method 4:
	// We first try from 4-th floor. Two cases arise,
	// 		1. If egg breaks, we have one egg left so we need three more trials.
	// 		2. If egg does not break, we try next from 7-th floor. Again two cases arise.
	// We can say that
	// &Sum;xCj  >= k
	// 1 <= i <= n
	// Basically we need to find minimum value of x
	// that satisfies above inequality. We can find
	// such x using Binary Search.
	// Time Complexity: O(nlog(k))
	// Space Complexity: O(n)
	long long low = 1, high = k;
	while (low < high) {
		long long mid = (low + high) / 2;
		if (bin_coeff(mid, N) < k) {
			low = mid + 1;
		}
		else {
			high = mid;
		}
	}
	cout << low << endl;
	return 0;
}