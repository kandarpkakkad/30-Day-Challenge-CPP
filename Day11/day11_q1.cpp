#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/nth-root-of-a-number-using-log/

	Input:
	125 3

	Output:
	5
*/

double kth_root(double N, long long k) {
	if (N == 0.0 || N == 1.0) {
		return N;
	}
	double low = 1.0, high = N, ans = 0;
	while (low <= high) {
		double mid = (low + high) / 2;
		double mid_k = pow(mid, k);
		if (mid_k == N) {
			return mid;
		}
		if (mid_k < N) {
			low = mid + 0.000000001;
			ans = mid;
		}
		else {
			high = mid - 0.000000001;
		}
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	double N;
	long long k;
	cin >> N >> k;

	// Method 1:
	// Logarithmic solution.
	// Time Complexity: O(log(log(n)))
	// Space Complexity: O(1)
	// cout << pow(k, (1.0 / k) * log(N) / log(k)) << endl;

	// Method 2:
	// Binary search
	// Time Complexity: O(log(n)^2)
	// Space Complexity: O(1)
	double ans = kth_root(N, k);
	cout << ans << endl;
	return 0;
}