#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/partition-equal-subset-sum/

	Input:
	4
	1 5 11 5

	Output:
	True

	Input:
	1 2 3 5

	Output:
	False
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
	// For each number, we can pick it or not. Let us assume dp[i][j] means whether the specific sum j can be gotten from the first i numbers. If we can pick such a series of numbers from 0-i whose sum is j, dp[i][j] is true, otherwise it is false.
	// Time Complexity: O(n * sum)
	// Space Complexity: O(sum)
	long long sum = 0;
	for (long long i = 0; i < N; i++) {
		sum += arr[i];
	}
	if (sum % 2 == 1) {
		cout << "False" << endl;
	}
	else {
		bool dp[sum + 1] = {false};
		dp[0] = true;
		for (long long i = 0; i < N; i++) {
			for (long long j = sum; j > 0; j--) {
				if (j >= arr[i]) {
					dp[j] = dp[j] || dp[j - arr[i]];
				}
			}
		}
		if (dp[sum]) {
			cout << "True" << endl;
		}
		else {
			cout << "False" << endl;
		}
	}
	return 0;
}