#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/combination-sum/

	Input:
	4 7
	2 3 6 7

	Output:
	2 2 3
	7
*/

void solve(vector<long long> &candidates, long long target, vector<vector<long long>> &ans, vector<long long> &combination, long long begin) {
	if (!target) {
		ans.push_back(combination);
		return;
	}
	for (long long i = begin; i < candidates.size() && target >= candidates[i]; i++) {
		combination.push_back(candidates[i]);
		solve(candidates, target - candidates[i], ans, combination, i);
		combination.pop_back();
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	vector<long long> candidates;
	long long t;
	for (long long i = 0; i < N; i++) {
		cin >> t;
		candidates.push_back(t);
	}

	// Method 1:
	// We sort the array and check if the sum of subsequence is equal to target.
	// Time Complexity: O(2^n)
	// Space Complexity: O(n)
	vector<vector<long long>> ans;
	vector<long long> combination;
	sort(candidates.begin(), candidates.end());
	solve(candidates, k, ans, combination, 0);
	if (ans.size()) {
		for (long long i = 0; i < ans.size(); i++) {
			for (long long j = 0; j < ans[i].size(); j++) {
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "No Solution" << endl;
	}
	return 0;
}