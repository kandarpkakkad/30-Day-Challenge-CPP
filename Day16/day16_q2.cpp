#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/?ref=rp

	Input:
	ABCBABCBABCBACBABC
	ABC

	Output:
	Pattern at: 0 to 3
	Pattern at: 4 to 7
	Pattern at: 8 to 11
	Pattern at: 15 to 18
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string str, pat;
	getline(cin, str);
	getline(cin, pat);
	long long N = str.length();
	long long M = pat.length();

	// The basic idea behind KMP’s algorithm is: whenever we detect a mismatch (after some matches), we already know some of the characters in the text of the next window.
	// We compare first window of txt with pat
	// txt = "AAAAABAAABA"
	// pat = "AAAA"  [Initial position]
	// We find a match. This is same as Naive String Matching.
	// In the next step, we compare next window of txt with pat.
	// txt = "AAAAABAAABA"
	// pat =  "AAAA" [Pattern shifted one position]
	// This is where KMP does optimization over Naive. In this
	// second window, we only compare fourth A of pattern
	// with fourth character of current window of text to decide
	// whether current window matches or not. Since we know
	// first three characters will anyway match, we skipped
	// matching first three characters.
	// Need of Preprocessing?
	// An important question arises from the above explanation,
	// how to know how many characters to be skipped. To know this,
	// we pre-process pattern and prepare an integer array
	// lps[] that tells us the count of characters to be skipped.
	// lps means Longest Proper Prefix which is also suffix.
	// We search for lps in sub-patterns. More clearly we focus on sub-strings of patterns that are either prefix and suffix.
	// For each sub-pattern pat[0..i] where i = 0 to m-1, lps[i] stores length of the maximum matching proper prefix which is also a suffix of the sub-pattern pat[0..i].
	// We use a value from lps[] to decide the next characters to be matched. The idea is to not match a character that we know will anyway match.
	// Time Complexity: O(max(n, m))
	// Space Complexity: O(m)
	long long lps[M];
	lps[0] = 0;
	long long len = 0;
	long long i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if (len != 0) {
				len = lps[len - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
	i = 0;
	long long j = 0;
	while (i < N) {
		if (pat[j] == str[i]) {
			j++;
			i++;
		}
		if (j == M) {
			cout << "Pattern at: " << i - j << " to " << i << endl;
			j = lps[j - 1];
		}
		else if (i < N && pat[j] != str[i]) {
			if (j != 0) {
				j = lps[j - 1];
			}
			else {
				i++;
			}
		}
	}
	return 0;
}