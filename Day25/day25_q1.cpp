#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/maximum-product-subarray/

	Input:
	4
	2 3 -2 4

	Output:

*/

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
	// We will keep 2 pointers l and r to calculate prefix and suffix in A respectively. Then we return the maximum of prefix and suffix.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long ans = arr[0], l = 0, r = 0;
	for (long long i = 0; i < N; i++) {
		if (l == 0) {
			l = 1;
		}
		if (r == 0) {
			r = 1;
		}
		l = l * arr[i];
		r = r * arr[N - 1 - i];
		ans = max(ans, max(l, r));
	}
	cout << "Maximum product: " << ans << endl;
	return 0;
}