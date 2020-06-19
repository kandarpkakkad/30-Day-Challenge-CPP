#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/4sum/

	Input:
	7 16
	1 2 3 4 5 6 7

	Output:
	1 2 6 7
	1 3 5 7
	1 4 5 6
	2 3 4 7
	2 3 5 6

	1 2 6 7
	1 3 5 7
	1 4 5 6
	2 3 4 7
	2 3 5 6
*/

vector<vector<long long>> k_sum(long long arr[], long long N, long long k, long long x, long long start) {
	vector<vector<long long>> ans;
	if (k == 2) {
		long long i = start, j = N - 1;
		while (i < j) {
			if (arr[i] + arr[j] < x) {
				i++;
			}
			else if (arr[i] + arr[j] > x) {
				j--;
			}
			else {
				ans.push_back({arr[i], arr[j]});
				while (i < j && arr[i] == arr[i + 1]) {
					i++;
				}
				while (i < j && arr[j] == arr[j - 1]) {
					j--;
				}
				i++;
				j--;
			}
		}
		return ans;
	}
	for (long long i = start; i < N - k + 1; i++) {
		if (i != start && arr[i] == arr[i - 1]) {
			continue;
		}
		vector<vector<long long>> a = k_sum(arr, N, k - 1, x - arr[i], i + 1);
		if (a.size() > 0) {
			for (long long j = 0; j < a.size(); j++) {
				a[j].push_back(arr[i]);
			}
			for (long long j = 0; j < a.size(); j++) {
				ans.push_back(a[j]);
			}
		}
	}
	return ans;
}

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
	// We will add 2 - 2 elements and add it in map to find the other 2 elements.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	sort(arr, arr + N);
	vector<long long> v;
	set<vector<long long>> s;
	vector<vector<long long>> ans;
	unordered_map<long long, vector<pair<long long, long long>>> mp;
	for (long long i = 0; i < N; i++) {
		for (long long j = i + 1; j < N; j++) {
			mp[arr[i] + arr[j]].push_back({i, j});
		}
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = i + 1; j < N; j++) {
			long long sum = arr[i] + arr[j];
			if (mp.find(x - sum) != mp.end()) {
				vector<pair<long long, long long>> p = mp[x - sum];
				for (long long k = 0; k < p.size(); k++) {
					if (p[k].first != i && p[k].first != j && p[k].second != j && p[k].second != i) {
						v.clear();
						v.push_back(arr[i]);
						v.push_back(arr[j]);
						v.push_back(arr[p[k].first]);
						v.push_back(arr[p[k].second]);
						sort(v.begin(), v.end());
						s.insert(v);
					}
				}
			}
		}
	}
	for (auto x = s.begin(); x != s.end(); x++) {
		ans.push_back(*x);
	}
	for (long long i = 0; i < ans.size(); i++) {
		for (long long j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Method 2:
	// Same method but we will generalize it to k sum where k >= 2 with recursive method.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	ans.clear();
	long long k = 4;
	if (N >= k) {
		ans = k_sum(arr, N, k, x, 0);
	}
	if (ans.size() > 0) {
		for (long long i = 0; i < ans.size(); i++) {
			sort(ans[i].begin(), ans[i].end());
			for (long long j = 0; j < ans[i].size(); j++) {
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else {
		cout << "No Solution" << endl;
	}
	return 0;
}