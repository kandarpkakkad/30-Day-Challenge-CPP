#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/power-of-two

	Input:
	1024

	Output:
	Yes
	Yes
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// We divide the number by 2 till the number becomes odd. If the number is power of two, the only time it will become odd is when number becomes 1.
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	long long t = N;
	if (t <= 0) {
		cout << "No" << endl;
	}
	else {
		while (t % 2 == 0) {
			t /= 2;
		}
		if (t == 1) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

	// Method 2:
	// <----- binary ---->
	//  n      n    n-1   n&(n-1)
	// --   ----   ----   -------
	//  0   0000   0111    0000 *
	//  1   0001   0000    0000 *
	//  2   0010   0001    0000 *
	//  3   0011   0010    0010
	//  4   0100   0011    0000 *
	//  5   0101   0100    0100
	//  6   0110   0101    0100
	//  7   0111   0110    0110
	//  8   1000   0111    0000 *
	//  9   1001   1000    1000
	// 10   1010   1001    1000
	// 11   1011   1010    1010
	// 12   1100   1011    1000
	// 13   1101   1100    1100
	// 14   1110   1101    1100
	// 15   1111   1110    1110
	// n & (n - 1) = 0 represents power of 2 for n > 0.
	// Time Complexity: O(1)
	// Space Complexity: O(1)
	if (N > 0 && (N & (N - 1)) == 0) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}