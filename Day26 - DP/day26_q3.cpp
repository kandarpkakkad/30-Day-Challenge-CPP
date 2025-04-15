#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/partition-equal-subset-sum/

	Input:
	6 9
	3 34 4 12 5 2

	Output:
	Found a subset
	Found a subset
	Found a subset
*/

bool is_subset_sum(long long arr[], long long n, long long sum) {
	if (sum == 0) {
		return true;
	}
	if (n == 0) {
		return false;
	}
	if (arr[n - 1] > sum) {
		return is_subset_sum(arr, n - 1, sum);
	}
	return is_subset_sum(arr, n - 1, sum) || is_subset_sum(arr, n - 1, sum - arr[n - 1]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, sum;
	cin >> N >> sum;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// We will do recursion with 2 steps:
	// 		1. Consider the last element and now the required sum = target sum – value of ‘last’ element and number of elements = total elements – 1
	// 		2. Leave the ‘last’ element and now the required sum = target sum and number of elements = total elements – 1
	// Time Complexity: O(exp(n))
	// Space Complexity: O()
	if (is_subset_sum(arr, N, sum)) {
		cout << "Found a subset" << endl;
	}
	else {
		cout << "Did not find any subset" << endl;
	}

	// Method 2:
	//  The approach for the problem is:
	// if (A[i] > j)
	// 		DP[i][j] = DP[i-1][j]
	// else
	// 		DP[i][j] = DP[i-1][j] OR DP[i-1][sum-A[i]]
	// 1. This means that if current element has value greater than ‘current sum value’ we will copy the answer for previous cases
	// 2. And if the current sum value is greater than the ‘ith’ element we will see if any of previous states have already experienced the sum=’j’ OR any previous states experienced a value ‘j – A[i]’ which will solve our purpose.
	// Time Complexity: O(n*sum)
	// Space Complexity: O(n*sum)
	bool subset[N + 1][sum + 1];
	for (long long i = 0; i <= N; i++) {
		subset[i][0] = true;
	}
	for (long long i = 0; i <= sum; i++) {
		subset[0][i] = false;
	}
	for (long long i = 1; i <= N; i++) {
		for (long long j = 1; j <= sum; j++) {
			if (j < arr[i - 1]) {
				subset[i][j] = subset[i - 1][j];
			}
			else {
				subset[i][j] = subset[i - 1][j] || subset[i - 1][j - arr[i - 1]];
			}
		}
	}
	if (subset[N][sum]) {
		cout << "Found a subset" << endl;
	}
	else {
		cout << "Did not find any subset" << endl;
	}

	// Method 3:
	// The solution discussed above requires O(n * sum) space and O(n * sum) time. We can optimize space. We create a boolean 2D array subset[2][sum+1]. Using bottom up manner we can fill up this table. The idea behind using 2 in “subset[2][sum+1]” is that for filling a row only the values from previous row is required. So alternate rows are used either making the first one as current and second as previous or the first as previous and second as current.
	// Time Complexity: O(n*sum)
	// Space Complexity: O(sum)
	bool dp[2][sum + 1];
	dp[0][0] = false;
	for (long long i = 0; i <= N; i++) {
		for (long long j = 0; j <= sum; j++) {
			if (j == 0) {
				dp[i % 2][j] = true;
			}
			else if (i == 0) {
				dp[i % 2][j] = false;
			}
			if (arr[i - 1] <= j) {
				dp[i % 2][j] = dp[(i + 1) % 2][j - arr[i - 1]] || dp[(i + 1) % 2][j];
			}
			else {
				dp[i][j] = dp[(i + 1) % 2][j];
			}
		}
	}
	if (dp[N % 2][sum]) {
		cout << "Found a subset" << endl;
	}
	else {
		cout << "Did not find any subset" << endl;
	}
	return 0;
}