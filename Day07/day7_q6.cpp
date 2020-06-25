#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/max-consecutive-ones/#:~:text=Input%3A%20%5B1%2C1%2C,of%20consecutive%201s%20is%203.

	Input:
	12
	0 1 1 1 1 0 0 1 1 0 1 1

	Output:
	4
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
	// We keep 2 pointers, 1 for calculating ans and other for number of consecutive ones.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long cons = 0, ans = 0;
	for (long long i = 0; i < N; i++) {
		if (arr[i] == 1) {
			cons++;
		}
		else {
			cons = 0;
		}
		ans = max(ans, cons);
	}
	cout << ans << endl;
	return 0;
}