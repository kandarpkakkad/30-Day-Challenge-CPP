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
	// We find maximum and traverse left and right of maximum to see how much water can be stored.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long ans = 0;
	long long max_pos = 0;
	long long l_max, r_max;
	for (long long i = 0; i < N; i++) {
		if (arr[i] > arr[max_pos]) {
			max_pos = i;
		}
	}

	l_max = arr[0];
	for (long long i = 0; i <= max_pos; i++) {
		if (arr[i] < l_max) {
			ans += (l_max - arr[i]);
		}
		else {
			l_max = arr[i];
		}
	}

	r_max = arr[N - 1];
	for (long long i = N - 1; i >= max_pos; i--) {
		if (arr[i] < r_max) {
			ans += (r_max - arr[i]);
		}
		else {
			r_max = arr[i];
		}
	}
	cout << ans << endl;
	return 0;
}