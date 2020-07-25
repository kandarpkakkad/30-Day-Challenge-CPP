#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/longest-common-subsequence/

	Input:
	abcde
	ace

	Output:
	3
	3
*/

long long lcs(string &a, string &b) {
	if (a.size() < b.size()) {
		return lcs(b, a);
	}
	vector<vector<int>> m(2, vector<int>(b.size() + 1));
	for (long long i = 1; i <= a.size(); i++) {
		for (long long j = 1; j <= b.size(); j++) {
			if (a[i - 1] == b[j - 1]) {
				m[i % 2][j] = m[(i - 1) % 2][j - 1] + 1;
			}
			else {
				m[i % 2][j] = max(m[(i - 1) % 2][j], m[i % 2][j - 1]);
			}
		}
	}
	return m[a.size() % 2][b.size()];
}

long long lcs2(string &a, string &b, long long i, long long j) {
	if (i <= 0 || j <= 0) {
		return 0;
	}
	if (a[i - 1] == b[j - 1]) {
		return 1 + lcs2(a, b, i - 1,  j - 1);
	}
	else {
		return max(lcs2(a, b, i, j - 1), lcs2(a, b, i - 1, j));
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s1, s2;
	cin >> s1 >> s2;
	long long N = s1.length();
	long long M = s2.length();

	// Method 1:
	// We use Bottum-up DP and track each combination of i and j. If a[i] == b[j], lcs for i and j would be 1 + lcs till i - 1 and j - 1 indices. Else we will take the largest lcs if we skip a character from one of the string i.e. max(m[i - 1][j], m[i][j - 1]).
	// You may notice that we are only looking one row up in the solution above. So, we just need to store two rows.
	// Time Complexity: O(n*m)
	// Space Complexity O(min(n, m))
	cout << lcs(s1, s2) << endl;

	// Method 2:
	// We will do memoised recursion with DP to perform the same task above.
	// Time Complexity: O(2^(n+m))
	// Space Complexity: O(n+m)
	cout << lcs2(s1, s2, N, M) << endl;
	return 0;
}