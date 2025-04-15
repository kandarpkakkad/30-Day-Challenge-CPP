#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/longest-palindromic-substring/

	Input:
	abcdcbabcdef

	Output:
	abcdcba
	7
	abcdcba
	7
	abcdcba
	7
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string str;
	cin >> str;
	long long N = str.length();

	// Method 1:
	// Naive brute force approach. We check each substring whether it is palindrome or not.
	// Time Complexity: O(n^3)
	// Space Complexity: O(1)
	long long max_length = 1, start = 0;
	for (long long i = 0; i < N; i++) {
		for (long long j = i; j < N; j++) {
			bool flag = true;
			for (long long k = 0; k < (j - i + 1) / 2; k++) {
				if (str[i + k] != str[j - k]) {
					flag = false;
				}
			}
			if (flag && (j - i + 1) > max_length) {
				start = i;
				max_length = j - i + 1;
			}
		}
	}
	for (long long i = start; i <= start + max_length - 1; i++) {
		cout << str[i];
	}
	cout << endl;
	cout << max_length << endl;

	// Method 2:
	// We will store the results of subproblems in 2D boolean array. The value of table[i][j] is true if substring is palindrome else false. The value table[i][j] is true is table[i + 1][j - 1] is true and str[i] = str[j], else false.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2)
	bool table[N][N];
	memset(table, false, sizeof(table));
	for (long long i = 0; i < N; i++) {
		table[i][i] = true;
	}
	max_length = 1;
	start = 0;
	for (long long i = 0; i < N - 1; i++) {
		if (str[i] == str[i + 1]) {
			table[i][i + 1] = true;
			start = i;
			max_length = 2;
		}
	}
	for (long long k = 3; k <= N; k++) {
		for (long long i = 0; i < N - k + 1; i++) {
			long long j = i + k - 1;
			if (table[i + 1][j - 1] && str[i] == str[j]) {
				table[i][j] = true;
				if (k > max_length) {
					start = i;
					max_length = k;
				}
			}
		}
	}
	for (long long i = start; i < start + max_length; i++) {
		cout << str[i];
	}
	cout << endl;
	cout << max_length << endl;

	// Method 3:
	// We will use the same idea from previous method but instead of storing we will find even and odd length palindromes and keep the track of longest one.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	max_length = 1;
	start = 0;
	long long low, high;
	for (long long i = 1; i < N; i++) {
		// Even length palindrome
		low = i - 1;
		high = i;
		while (low >= 0 && high < N && str[low] == str[high]) {
			if (high - low + 1 > max_length) {
				start = low;
				max_length = high - low + 1;
			}
			low--;
			high++;
		}
		// Odd length palindrome
		low = i - 1;
		high = i + 1;
		while (low >= 0 && high < N && str[low] == str[high]) {
			if (high - low + 1 > max_length) {
				start = low;
				max_length = high - low + 1;
			}
			low--;
			high++;
		}
	}
	for (long long i = start; i < start + max_length; i++) {
		cout << str[i];
	}
	cout << endl;
	cout << max_length << endl;
	return 0;
}