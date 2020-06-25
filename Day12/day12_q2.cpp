#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/counting-bits

	Input:
	15

	Output:
	0 1 1 2 1 2 2 3 1 2 2 3 2 3 3 4
	0 1 1 2 1 2 2 3 1 2 2 3 2 3 3 4
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// As we know i&(i - 1) drops the lowest set bit, and hence we increament the number of ones in i&(i - 1)th position.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	long long ans[N + 1] = {0};
	for (long long i = 1; i <= N; i++) {
		ans[i] = ans[i & (i - 1)] + 1;
	}
	for (long long i = 0; i <= N; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

	// Method 2:
	// We use built-in function to find 1s which takes sizeof(long long) time to find number of ones.
	// Time Complexity: O(n*sizeof(long long))
	// Space Complexity: O(n)
	vector<long long> v;
	for (long long i = 0; i <= N; i++) {
		bitset<32> b(i);
		long long n = b.count();
		v.push_back(n);
	}
	for (long long i = 0; i <= N; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	return 0;
}