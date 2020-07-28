#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/minimum-path-sum/
	https://www.geeksforgeeks.org/maximum-path-sum-matrix/

	You need to run the methods separately.

	Input:
	3 3
	1 3 1
	1 5 1
	4 2 1

	Output:
	12
	7
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long arr[N][M];
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	// Method 1: (Max sum)
	// First we find the max value in first row and store it in ans. Now for every element in matrix, update element with max value which can be included in max path. If the value is greater than ans, update ans.
	// Time Complexity: O(n*m)
	// Space Complexity: O(1)
	for (long long i = 1; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (j > 0 && j < M - 1) {
				arr[i][j] += max(arr[i - 1][j], max(arr[i - 1][j - 1], arr[i - 1][j + 1]));
			}
			else if (j > 0) {
				arr[i][j] += max(arr[i - 1][j], arr[i - 1][j - 1]);
			}
			else if (j < M - 1) {
				arr[i][j] +=  max(arr[i - 1][j], arr[i - 1][j + 1]);
			}
		}
	}
	long long ans = 0;
	for (long long i = 0; i < M; i++) {
		ans = max(ans, arr[N - 1][i]);
	}
	cout << ans << endl;

	// Method 1: (Min sum)
	// The idea is to store the ans of the subproblems
	// Time Complexity: O(n*m)
	// Space Complexity: O(n)
	long long curr[N];
	for (long long i = 0; i < N; i++) {
		curr[i] = arr[0][0];
	}
	for (long long i = 1; i < N; i++) {
		curr[i] = curr[i - 1] + arr[i][0];
	}
	for (long long i = 1; i < M; i++) {
		curr[0] += arr[0][i];
		for (long long j = 1; j < N; j++) {
			curr[j] = min(curr[j - 1], curr[j]) + arr[j][i];
		}
	}
	cout << curr[N - 1] << endl;
	return 0;
}