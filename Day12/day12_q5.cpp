#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/find-significant-set-bit-number/

	Input:
	273

	Output:
	256
	256
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// We find last 1 in the binary of the number.
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	long long t = N;
	long long msb = 0;
	while (t != 0) {
		t /= 2;
		msb++;
	}
	msb--;
	cout << (1 << msb) << endl;

	// Method 2:
	// Another method is to one by one set bits, then add 1 so that only the bit after MSB is set. Finally right shift by 1.
	// Time Complexity: O(1)
	// Space Complexity: O(1)
	t = N;
	t |= t >> 1;
	t |= t >> 2;
	t |= t >> 4;
	t |= t >> 8;
	t |= t >> 16;
	t = t + 1;
	cout << (t >> 1) << endl;
	return 0;
}