#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/subsets/

	Input:
	5
	1 2 3 4 5

	Output:
	Empty
	1
	2
	1 2
	3
	1 3
	2 3
	1 2 3
	4
	1 4
	2 4
	1 2 4
	3 4
	1 3 4
	2 3 4
	1 2 3 4
	5
	1 5
	2 5
	1 2 5
	3 5
	1 3 5
	2 3 5
	1 2 3 5
	4 5
	1 4 5
	2 4 5
	1 2 4 5
	3 4 5
	1 3 4 5
	2 3 4 5
	1 2 3 4 5
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
	// We will create a bitmask of length N ans alter the positions of set bits for permutations.
	// Time Complexity: O(n*2^n)
	// Space Complexity: O(2^n)
	sort(arr, arr + N);
	long long fn = pow(2, N);
	vector<vector<long long>> ans(fn, vector<long long>());
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < fn; j++) {
			if ((j >> i) % 2 == 1) {
				ans[j].push_back(arr[i]);
			}
		}
	}
	for (long long i = 0; i < ans.size(); i++) {
		if (ans[i].empty()) {
			cout << "Empty" << endl;
		}
		else {
			for (long long j = 0; j < ans[i].size(); j++) {
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}