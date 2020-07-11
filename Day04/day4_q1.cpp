#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/two-sum/

	Input:
	7 8
	1 2 3 4 5 6 7

	Output:
	1 7
	2 6
	3 5

	3 5
	2 6
	1 7
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, x;
	cin >> N >> x;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// We first sort the array and then we keep two pointers one at the beginnning and one at the last number smaller than x. Then we add them and see if sum is equal, greater or smaller than x and act accordingly.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n)
	sort(arr, arr + N);
	long long pos1 = 0, pos2 = N - 1;
	while (arr[pos2] > x && pos2 > 0) {
		pos2--;
	}
	if (pos2 <= 0) {
		cout << -1 << endl;
	}
	else {
		vector<pair<long long, long long>> res;
		bool f = false;
		while (pos1 < pos2) {
			if (arr[pos1] + arr[pos2] == x) {
				f = true;
				res.push_back({pos1 + 1, pos2 + 1});
				pos1++;
				pos2--;
			}
			else if (arr[pos1] + arr[pos2] > x) {
				pos2--;
			}
			else {
				pos1++;
			}
		}
		if (!f) {
			cout << -1 << endl;
		}
		else {
			for (long long i = 0; i < res.size(); i++) {
				cout << res[i].first << " " << res[i].second << endl;
			}
			cout << endl;
		}
	}
	// Method 2:
	// We keep a dictionary to save key->value pairs and search it to find the sum.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	unordered_map<long long, long long> dic;
	vector<pair<long long, long long>> ans;
	bool flag = false;
	long long ans1 = 0, ans2 = 0;
	for (long long i = 0; i <  N; i++) {
		if (dic.find(x - arr[i]) != dic.end() && dic[x - arr[i]] != i) {
			flag = true;
			ans1 = dic[x - arr[i]];
			ans2 = i;
			ans.push_back({ans1 + 1, ans2 + 1});
		}
		dic[arr[i]] = i;
	}
	if (flag) {
		for (long long i = 0; i < ans.size(); i++) {
			cout << ans[i].first << " " << ans[i].second << endl;
		}
	}
	else {
		cout << -1 << endl;
	}
	return 0;
}
