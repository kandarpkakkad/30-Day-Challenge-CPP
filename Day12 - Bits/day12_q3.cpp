#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/divide-two-integers

	Input:
	15 -5

	Output:
	-3

	Input:
	15 7

	Output:
	2
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;

	// Method 1:
	// The key observation is that the quotient of a division is just the number of times that we can subtract the divisor from the dividend without making it negative.
	// Time Complexity: O(log(n)^2)
	// Space Complexity: O(1)
	if (M == LLONG_MIN && N == -1) {
		cout << LLONG_MAX << endl;
	}
	else {
		long long m = abs(M), n = abs(N), ans = 0;
		long long sign = M > 0 ^ N > 0 ? -1 : 1;
		while (n >= m) {
			long long temp = m, temp2 = 1;
			while (temp << 1 <= n) {
				temp <<= 1;
				temp2 <<= 1;
			}
			n -= temp;
			ans += temp2;
		}
		if (sign == -1) {
			cout << -ans << endl;
		}
		else {
			cout << ans << endl;
		}
	}
	return 0;
}