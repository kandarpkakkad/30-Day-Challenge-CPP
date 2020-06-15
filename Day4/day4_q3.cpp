#include<bits/stdc++.h>

using namespace std;

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
	// In hash, find if arr[i] - 1 is present or not, if not its the starting point of subsequence and check if all the further elements are present in hash or not, if present, continue to the next element.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	long long curr, ans = 1;
	unordered_set<long long> s;
	for (long long i = 0; i < N; i++) {
		s.insert(arr[i]);
	}
	for (long long i = 0; i < N; i++) {
		if (s.find(arr[i] - 1) == s.end()) {
			curr = 1;
			bool flag = false;
			while (!flag) {
				if (s.find(arr[i] + curr) != s.end()) {
					curr++;
				}
				else {
					flag = true;
				}
			}
			ans = max(ans, curr);
		}
	}
	cout << ans << endl;

	// Method 2:
	// Logic remains the same but instead of set we use map.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	map<long long, long long> m;
	for (long long i = 0; i < N; i++) {
		m[arr[i]] = 1;
	}
	auto it = m.begin();
	long long x = it->first;
	long long c = 1;
	ans = 1;
	for (auto it = m.begin(); it != m.end(); it++) {
		if (it->first - 1 == x) {
			c++;
			ans = max(ans, c);
		}
		else {
			c = 1;
		}
		x = it->first;
	}
	cout << ans << endl;
	return 0;
}