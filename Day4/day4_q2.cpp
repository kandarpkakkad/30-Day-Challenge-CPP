#include<bits/stdc++.h>

using namespace std;

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
					if (p[k].first != i && p[k].first != i && p[k].second != j && p[k].second != i) {
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
	return 0;
}