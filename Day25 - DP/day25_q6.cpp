#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/maximum-sum-increasing-subsequence-dp-14/

	Input:
	7
	1 101 2 3 100 4 5

	Output:
	106
*/

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
	// We keep an array for every element and add the numbers if they are greater than the current sum from that element.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	long long ans = 0;
	long long dp[N];
	for (long long i = 0; i < N; i++) {
		dp[i] = arr[i];
	}
	for (long long i = 1; i < N; i++) {
		for (long long j = 0; j < i; j++) {
			if (arr[i] > arr[j] && dp[i] < dp[j] + arr[i]) {
				dp[i] = dp[j] + arr[i];
			}
		}
	}
	for (long long i = 0; i < N; i++) {
		if (ans < dp[i]) {
			ans = dp[i];
		}
	}
	cout << ans << endl;
	return 0;
}