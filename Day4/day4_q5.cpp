#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// Brute force approach to find xor sum = k by traversing loop inside a loop.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	long long ans = 0;
	for (long long i = 0; i < N; i++) {
		long long xor_sum = 0;
		for (long long j = i; j < N; j++) {
			xor_sum ^= arr[j];
			if (xor_sum == k) {
				ans++;
			}
		}
	}
	cout << ans << endl;

	// Method 2:
	// We will compute prefix xor_sum and store it in a map and traverse the map to see if the xor sum is k or not.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	ans = 0;
	long long prexorsum[N];
	unordered_map<long long, long long> mp;
	prexorsum[0] = arr[0];
	for (long long i = 1; i < N; i++) {
		prexorsum[i] = prexorsum[i - 1] ^ arr[i];
	}
	for (long long i = 0; i < N; i++) {
		long long temp = k ^ prexorsum[i];
		ans = ans + mp[temp];
		if (prexorsum[i] == k) {
			ans++;
		}
		mp[prexorsum[i]]++;
	}
	cout << ans << endl;
	return 0;
}