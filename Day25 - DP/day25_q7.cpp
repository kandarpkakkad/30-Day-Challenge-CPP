#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/burst-balloons

	Input:
	5
	5 4 6 2 7

	Output:
	158
	158
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
	// We will use 2D DP array to store the possible multiplication ways and find the minimum of it.
	// Time Complexity: O(n^3)
	// Space Complexity: O(n^2)
	long long dp[N][N];
	for (long long i = 0; i < N; i++) {
		dp[0][i] = 0;
		dp[i][0] = 0;
		dp[i][i] = 0;
	}
	for (long long d = 1; d < N - 1; d++) {
		for (long long i = 1; i < N - d; i++) {
			long long k = i + d;
			long long mn = LLONG_MAX;
			for (long long j = 1; j <= k - 1; j++) {
				long long temp = dp[i][j] + dp[j + 1][k] + arr[i - 1] * arr[j] * arr[k];
				if (temp < mn) {
					mn = temp;

				}
			}
			dp[i][k] = mn;
		}
	}
	cout << dp[1][N - 1] << endl;

	// Method 2:
	// We will do the same approach but now we will not store all the possibility in temp. Instead we will manually calculate all possibilities and take minimum of it.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	long long dp2[N][N];
	for (long long i = 0; i < N; i++) {
		dp2[i][i] = 0;
		dp2[i][0] = 0;
		dp2[0][i] = 0;
	}
	for (long long i = 1; i < N - 1; i++) {
		for (long long j = 1; j < N - i; j++) {
			dp2[j][j + i] = min(
			                    dp2[j + 1][j + i] + arr[j - 1] * arr[j] * arr[j + i],
			                    dp2[j][j + i - 1] + arr[j - 1] * arr[j + i - 1] * arr[j + i]
			                );
		}
	}
	cout << dp2[1][N - 1] << endl;
	return 0;
}