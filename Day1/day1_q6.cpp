#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	vector<vector<long long>> arr;
	long long u, v;
	for (long long i = 0; i < N; i++) {
		vector<long long> temp;
		cin >> u >> v;
		temp.push_back(u);
		temp.push_back(v);
		arr.push_back(temp);
	}

	// Method 1:
	// Here we are going to sort the array with respect to first element and then we will merge the intervals if they are overlapping.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	vector<vector<long long>> ans;
	if (arr.size() < 2) {
		for (long long i = 0; i < arr.size(); i++) {
			for (long long j = 0; j < arr[i].size(); j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		sort(arr.begin(), arr.end());
		ans.push_back(arr[0]);
		for (long long i = 0; i < arr.size(); i++) {
			if (arr[i][0] <= ans[ans.size() - 1][1]) {
				ans[ans.size() - 1][1] = max(ans[ans.size() - 1][1], arr[i][1]);
			}
			else {
				ans.push_back(arr[i]);
			}
		}
		for (long long i = 0; i < ans.size(); i++) {
			for (long long j = 0; j < ans[i].size(); j++) {
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}