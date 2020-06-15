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
	long long k = 0;

	// Method 1:
	// Here we will do longest subarray with sum = k where k = 0. We will store frequency in the hashmap and if the value is encountered in hashmap, answer is updated by frequecy of the value.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	unordered_map<long long, long long> mp = {{0, 1}};
	long long total = 0;
	long long ans = 0;
	for (long long i = 0; i < N; i++) {
		total += arr[i];
		ans += mp.count(total - k) ? mp[total - k] : 0;
		mp[total - k] = mp.count(total) ? mp[total] + 1 : 1;
	}
	cout << ans << endl;

	// Method 2;
	// Brute Force approach to see if sum = k where k = 0
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	ans = 0;
	for (long long i = 0; i < N; i++) {
		long long sum = arr[i];
		if (sum == k) {
			ans++;
		}
		for (long long j = i + 1; j < N; j++) {
			sum += arr[j];
			if (sum == k) {
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}