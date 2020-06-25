#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/greatest-common-divisor-of-strings

	Input:
	ABCABCABC
	ABC

	Output:
	ABC
*/

long long gcd(long long a, long long b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

string gcd_of_strings(string s1, string s2) {
	string ans = "";
	if (s1 + s2 != s2 + s1) {
		return ans;
	}
	long long N = s1.length();
	long long M = s2.length();
	if (N == M) {
		return s1;
	}
	long long min_size = N < M ? N : M;
	long long max_size = N > M ? N : M;
	min_size = gcd(min_size, max_size);
	for (long long i = 0; i < min_size; i++) {
		ans += s1[i];
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s1, s2;
	cin >> s1 >> s2;

	// Method 1:
	// we find gcd of lengths if s1 + s2 = s2 + s1. and return 1st gcd letters of the string.
	// Time Complexity: O(log(n))
	// Space Complexity: O(n)
	string ans = gcd_of_strings(s1, s2);
	cout << ans << endl;
	return 0;
}