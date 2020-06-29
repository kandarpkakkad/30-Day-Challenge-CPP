#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/

	Input:
	I am studying in Nirma University.
	Nirma University

	Output:
	Pattern at: 17 to 33

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
	getline(cin , str);
	getline(cin, pat);

	// Rabin-Karp is similar to naive method, but istead of directly checking characters we check the hash value. If the hash values match then the characters are checked.
	// hash( txt[s+1 .. s+m] ) = ( d ( hash( txt[s .. s+m-1]) – txt[s]*h ) + txt[s + m] ) mod q
	// hash( txt[s .. s+m-1] ) : Hash value at shift s.
	// hash( txt[s+1 .. s+m] ) : Hash value at next shift (or shift s+1)
	// d: Number of characters in the alphabet
	// q: A prime number
	// h: d^(m-1)
	long long d = 256;
	long long q = 101;
	long long N = str.length();
	long long M = pat.length();
	long long i, j;
	long long p = 0; // hash value for pattern
	long long t = 0; // hash value for string
	long long h = 1;
	for (i = 0; i < M - 1; i++) {
		h = (h * d) % q;
	}
	for (long long i = 0; i < M; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + str[i]) % q;
	}
	for (i = 0; i <= N - M; i++) {
		if (p == t) {
			for (j = 0; j < M; j++) {
				if (str[i + j] != pat[j]) {
					break;
				}
			}
			if (j == M) {
				cout << "Pattern at: " << i << " to " << i + M << endl;
			}
		}
		if (i < N - M) {
			t = (d * (t - str[i] * h) + str[i + M]) % q;
			if (t < 0) {
				t = t + q;
			}
		}
	}
	return 0;
}