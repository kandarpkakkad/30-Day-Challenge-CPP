#include<bits/stdc++.h>

using namespace std;

/*
	https://www.interviewbit.com/problems/rod-cutting/

	Input:
	8
	1 5 8 9 10 17 17 20

	Output:
	22
	22
*/

long long cut_rod(long long arr[], long long N) {
	if (N <= 0) {
		return 0;
	}
	long long max_val = LLONG_MIN;
	for (long long i = 0; i < N; i++) {
		max_val = max(max_val, arr[i] + cut_rod(arr, N - i - 1));
	}
	return max_val;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// With recursion we check all the possibilities of adding the numbers to the length of rod.
	// Time Complexity: O(2^n)
	// Space Complexity: O(2^n) (recursive stack)
	cout << cut_rod(arr, N) << endl;

	// Method 2:
	// We will follow the same procedure but as we can see we are calculating 1 value again and again. Instead we store it in an array i.e. DP memoization.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	long long dp[N + 1];
	dp[0] = 0;
	for (long long i = 1; i <= N; i++) {
		long long max_val = LLONG_MIN;
		for (long long j = 0; j < i; j++) {
			max_val = max(max_val, arr[j] + dp[i - j - 1]);
		}
		dp[i] = max_val;
	}
	cout << dp[N] << endl;
	return 0;
}