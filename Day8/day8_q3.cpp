#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/coin-change/

	Input:
	3 11
	1 2 5

	Output:
	3
*/

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
	// We sort the denominations in reverse order and check the number of coins required of a denomination.
	// Note that many answers in this method is wrong and hence we usually use DP solution.
	// Time Complexity: O(nlog(n))
	// Space Complexit: O(1)
	sort(arr, arr + N, greater<long long>());
	long long ans = 0;
	if (k == 0) {
		cout << 0 << endl;
	}
	else {
		for (long long i = 0; i < N; i++) {
			ans += (k / arr[i]);
			if (k / arr[i]) {
				k = k - (k / arr[i]) * arr[i];
			}
		}
		if (ans == 0) {
			cout << -1 << endl;
		}
		else {
			cout << ans << endl;
		}
	}
	return 0;
}