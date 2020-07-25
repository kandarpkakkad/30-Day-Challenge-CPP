#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/longest-increasing-subsequence/

	Input:
	8
	10 9 2 5 3 7 101 18

	Output:
	4
	4
*/

long long search(long long dp[], long long len, long long k) {
	long long left = 0;
	while (left <= len) {
		long long mid = (left + len) / 2;
		if (dp[mid] == k) {
			return mid;
		}
		else if (dp[mid] < k) {
			left = mid + 1;
		}
		else {
			len = mid - 1;
		}
	}
	return left;
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
	// We create a dp to store the number of elements less than the current element and then update answer if the that value is greater than answer.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	long long dp[N];
	for (long long i = 0; i < N; i++) {
		dp[i] = 1;
	}
	long long ans = 1;
	for (long long i = 1; i < N; i++) {
		for (long long j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;

	// Method 2:
	// We create dp again. But this time instead of calculating for all the possibilies keep tail value of each possible length.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n)
	long long dp2[N];
	dp2[0] = arr[0];
	long long len = 0;
	for (long long i = 1; i < N; i++) {
		if (arr[i] > dp2[len]) {
			dp2[++len] = arr[i];
		}
		else {
			long long ind = search(dp2, len, arr[i]);
			dp2[ind] = arr[i];
		}
	}
	cout << len + 1 << endl;
	return 0;
}