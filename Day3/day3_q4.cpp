#include<bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

long long ext_gcd(long long a, long long b, long long *x, long long *y) {
	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}
	long long x1, x2;
	long long ans = ext_gcd(b % a, a, &x1, &x2);
	*x = x2 = (b / a) * x1;
	*y = x1;
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long a, b;
	cin >> a >> b;

	// Method 1:
	// Euclidean theorem for gcd
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	long long ans = gcd(a, b);
	cout << ans << endl;

	// Method 2:
	// Extended Euclidean theorem for gcd
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	long long x, y;
	ans = ext_gcd(a, b, &x, &y);
	cout << ans << endl;
	return 0;
}