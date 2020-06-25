#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/factorial-trailing-zeroes/

	Input:
	15

	Output:
	3
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// Just need to find the occurance of 5 in factorial of the number given occurances of 5 is equal to number of trailing zeros.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long ans = 0;
	while (N) {
		ans += (N / 5);
		N /= 5;
	}
	cout << ans << endl;
	return 0;
}