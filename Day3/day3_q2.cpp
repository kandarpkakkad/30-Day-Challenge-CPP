#include<bits/stdc++.h>

using namespace std;

long long expo(double N, long long x) {
	if (x == 0) {
		return 1;
	}
	double temp = expo(N, x / 2);
	temp = temp * temp;
	if (x % 2 != 0) {
		temp *= N;
	}
	return temp;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	double N;
	long long x;
	cin >> N >> x;

	// Method 1:
	// We divide x by 2 everytime instead of traversing for x times.
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	double ans = expo(abs(N), abs(x));
	if (x < 0) {
		ans = (1.0 / ans) * 1.0;
	}
	if (N < 0) {
		if (x % 2 != 0) {
			ans = -1.0 * ans;
		}
	}
	cout << fixed << setprecision(11) << ans << endl;
	return 0;
}