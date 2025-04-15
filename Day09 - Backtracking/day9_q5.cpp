#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/permutations/

	Remeber that if the number repeats this method considers the repeated number as different number.

	Input:
	3
	1 2 3

	Output:
	1 2 3
	1 3 2
	2 1 3
	2 3 1
	3 1 2
	3 2 1
*/

void swap(long long &a, long long &b) {
	long long temp = a;
	a = b;
	b = temp;
}

void solve(vector<long long> arr, long long i, vector<vector<long long>> &ans) {
	if (i == arr.size() - 1) {
		ans.push_back(arr);
	}
	else {
		for (long long j = i; j < arr.size(); j++) {
			swap(arr[i], arr[j]);
			solve(arr, i + 1, ans);
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	vector<long long> arr;
	long long x;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		arr.push_back(x);
	}

	// Method 1:
	// We will change the position of a number (N-1)! times but through backtracking in recursive form.
	// Time Complexity: O(N!)
	// Space Complexity: O(N!)
	vector<vector<long long>> ans;
	solve(arr, 0, ans);
	for (long long i = 0; i < ans.size(); i++) {
		for (long long j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}