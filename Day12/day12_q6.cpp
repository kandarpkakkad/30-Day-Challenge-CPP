#include<bits/stdc++.h>

using namespace std;

/*
	https://www.techiedelight.com/find-square-number-without-using-multiplication-division-operator/

	Input:
	25

	Output:
	625
	625
	625
*/

long long sq(long long n) {
	if (n < 2) {
		return n;
	}
	n = abs(n);
	long long i = n >> 1;
	if (n % 2 == 1) {
		return ((sq(i) << 2) + (i << 2) + 1);
	}
	else {
		return (sq(i) << 2);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// Add odd numbers N times to result. Sum of n odd numbers = n^2.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long odd = 1;
	long long ans = 0;
	long long t = abs(N);
	while (t--) {
		ans += odd;
		odd += 2;
	}
	cout << ans << endl;

	// Method 2:
	// Add the number, number amount of times.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	t = abs(N);
	ans = t;
	for (long long i = 1; i < N; i++) {
		ans += t;
	}
	cout << ans << endl;

	// Method 3:
	// If N is even, n^2 = (n / 2)^4.
	// Else n^2 = (n/2)^4 + 4*(n/2) + 1.
	cout << sq(N) << endl;
	return 0;
}