#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/combination-sum-ii/

	Input:
	7 8
	10 1 2 7 6 1 5

	Output:
	1 1 6
	1 2 5
	1 7
	2 6
*/

void solve(vector<long long> &candidates, long long target, vector<vector<long long>> &ans, vector<long long> &combination, long long begin) {
	if (!target) {
		ans.push_back(combination);
		return;
	}
	for (long long i = begin; i < candidates.size() && target >= candidates[i]; i++) {
		if (i == begin | candidates[i] != candidates[i - 1]) {
			combination.push_back(candidates[i]);
			solve(candidates, target - candidates[i], ans, combination, i + 1);
			combination.pop_back();
		}
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
	// Each number can be used only once. Hence we will do a little change in the previous method. Instead of checking the same number, we will check next number.
	// Time Complexity: O(2^n)
	// Space Complexit: O(n)
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