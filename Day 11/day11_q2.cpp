#include<bits/stdc++.h>

using namespace std;

/*
	https://www.interviewbit.com/problems/matrix-median/

	Input:
	3 3
	1 3 5
	3 9 6
	2 6 9

	Output:
	5
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	vector<vector<long long>> arr;
	long long x;
	for (long long i = 0; i < N; i++) {
		vector<long long> r;
		for (long long j = 0; j < M; j++) {
			cin >> x;
			r.push_back(x);
		}
		arr.push_back(r);
	}
	for (long long i = 0; i < N; i++) {
		sort(arr[i].begin(), arr[i].end());
	}
	sort(arr.begin(), arr.end());

	// Method 1:
	// we find max and min and use binary search to find mid of min and max and get count less than mid and accordingly change min and max.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long mn = LLONG_MAX, mx = LLONG_MIN;
	for (long long i = 0; i < N; i++) {
		if (arr[i][0] < mn) {
			mn = arr[i][0];
		}
		if (arr[i][M - 1] > mx) {
			mx = arr[i][M - 1];
		}
	}
	long long required = (N * M + 1) / 2;
	while (mn < mx) {
		long long sum = 0;
		long long mid = (mn + mx) / 2;
		for (long long i = 0; i < N; i++) {
			sum += upper_bound(arr[i].begin(), arr[i].end(), mid) - arr[i].begin();
		}
		if (sum >= required) {
			mx = mid;
		}
		else {
			mn = mid + 1;
		}
	}
	cout << mn << endl;
	return 0;
}