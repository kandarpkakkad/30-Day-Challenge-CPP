#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/word-break/
	https://www.geeksforgeeks.org/word-break-problem-using-backtracking/

	Input:
	applepenapple
	2
	apple
	pen

	Output:
	apple pen apple

	Input:
	catsanddog
	5
	cats
	dog
	sand
	and
	cat

	Output:
	cat sand dog
	cats and dog
*/

bool is_in_dict(string &word, vector<string> dict) {
	for (long long i = 0; i < dict.size(); i++) {
		if (dict[i].compare(word) == 0) {
			return true;
		}
	}
	return false;
}

void solve(string s, long long N, string ans, vector<string> dict) {
	for (long long i = 1; i <= N; i++) {
		string prefix = s.substr(0, i);
		if (is_in_dict(prefix, dict)) {
			if (i == N) {
				ans += prefix;
				cout << ans << endl;
				return;
			}
			solve(s.substr(i, N - i), N - i, ans + prefix + " ", dict);
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	long long N;
	cin >> N;
	vector<string> dict;
	string t;
	for (long long i = 0; i < N; i++) {
		cin >> t;
		dict.push_back(t);
	}

	// Method 1;
	// We start scanning the sentence from left. As we find a valid word, we need to check whether rest of the sentence can make valid words or not. Because in some situations the first found word from left side can leave a remaining portion which is not further separable. So in that case we should come back and leave the current found word and keep on searching for the next word. And this process is recursive because to find out whether the right portion is separable or not, we need the same logic. So we will use recursion and backtracking to solve this problem.
	// Time Complexity: O((2^n) * s)
	// Space Complexity: O(n)
	string ans = "";
	solve(s, s.size(), ans, dict);
	return 0;
}