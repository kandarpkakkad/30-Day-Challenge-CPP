#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/maximum-profit-in-job-scheduling/

	Input:
	4
	1 2 3 3
	3 4 5 6
	50 10 40 70

	Output:
	120
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long start[N], end[N], profit[N];
	for (long long i = 0; i < N; i++) {
		cin >> start[i];
	}
	for (long long i = 0; i < N; i++) {
		cin >> end[i];
	}
	for (long long i = 0; i < N; i++) {
		cin >> profit[i];
	}

	// Method 1:
	// We find maximum job whose finish time is prior to current's start.
	// Time Complexity: O(n^2) -> can be reduced to O(nlog(n))
	// Space Complexity: O(n)
	long long temp, idx;
	vector<vector<long long>> intervals(N, vector<long long>(3));
	for (long long i = 0; i < N; i++) {
		intervals[i][0] = start[i];
		intervals[i][1] = end[i];
		intervals[i][2] = profit[i];
	}
	sort(intervals.begin(), intervals.end(), [](auto & a, auto & b) {return a[1] < b[1];});
	vector<long long> dp(N);
	dp[0] = intervals[0][2];
	for (long long i = 1; i < N; i++) {
		idx = -1;
		// The below step can be optimized doing binary search.
		for (long long j = 1; j >= 0; j--) {
			if (intervals[j][1] <= intervals[i][0]) {
				idx = j;
				break;
			}
		}
		temp = (idx == -1) ? intervals[i][2] : (intervals[i][2] + dp[idx]);
		dp[i] = max(temp, dp[i - 1]);
	}
	cout << dp[N - 1] << endl;
	return 0;
}