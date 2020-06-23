#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/subset-sum-backtracking-4/

	Input:
	7 35
	10 7 5 18 12 20 15

	Output:
	10 7 18
	10 5 20
	5 18 12
	20 15
*/

void print_subset(vector<long long> t, long long M) {
	for (long long i = 0; i < M; i++) {
		cout << t[i] << " ";
	}
	cout << endl;
}

void solve(long long arr[], vector<long long> t, long long N, long long M, long long sum, long long i, long long const k) {
	if (k == sum) {
		print_subset(t, M);
		solve(arr, t, N, M - 1, sum - arr[i], i + 1, k);
		return;
	}
	for (long long j = i; j < N; j++) {
		t.push_back(arr[j]);
		solve(arr, t, N, M + 1, sum + arr[j], j + 1, k);
		t.pop_back();
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// we create all subsets and check if a subset has sum = k.
	// Time Complexity: O(2^n)
	// Space Complexity: O(n)
	vector<long long> tuple_s;
	solve(arr, tuple_s, N, 0, 0, 0, k);
	tuple_s.clear();
	return 0;
}