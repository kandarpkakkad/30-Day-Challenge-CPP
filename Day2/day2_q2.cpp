#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/pascals-triangle/

	Input:
	5

	Output:
	1
	1 1
	1 2 1
	1 3 3 1
	1 4 6 4 1
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// If N < 3 then print N rows each containing i elements.
	// Else 1st two rows contain 1 and 2 1s and nth row contains 1st and last element 1 and middle elements as sum of previous row's ith element + (i - 1)th element.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	vector<vector<long long>> ans;
	for (long long i = 1; i <= N; i++) {
		vector<long long> temp;
		if (i == 1) {
			temp.push_back((long long)1);
			ans.push_back(temp);
		}
		else {
			temp.push_back((long long)1);
			for (long long j = 2; j < i; j++) {
				temp.push_back(ans[ans.size() - 1][j - 1] + ans[ans.size() - 1][j - 2]);
			}
			temp.push_back((long long)1);
			ans.push_back(temp);
		}
	}
	for (long long i = 0; i < ans.size(); i++) {
		for (long long j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}