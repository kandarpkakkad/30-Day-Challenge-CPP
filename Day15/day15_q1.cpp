#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/reverse-words-in-a-string/

	Input:
	a good   example

	Output:
	example good a
	example good a

	Input:
	  Hello  World

	Output:
	World Hello
	World Hello
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	getline(cin, s);

	// Method 1:
	// We will skip the spaces and find only the words and when we find words we add it in the beginning of the answer.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	string result;
	long long pos = 0;
	for (long long i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			if (i > pos) {
				result = s.substr(pos, i - pos) + " " + result;
			}
			pos = i + 1;
		}
		else if (i == s.length() - 1) {
			result = s.substr(pos, s.length() - pos) + " " + result;
		}
	}
	result = result.substr(0, result.length() - 1);
	cout << result << endl;

	// Method 2:
	// This is rather simple solution. We remove the extra spaces from everywhere and then reverse the string. Then we reverse the words.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long len, start = 0, end = s.length() - 1;
	for (long long i = 0; i < s.length() && s[i] == ' '; i++) {
		start = i;
	}
	for (long long i = s.length() - 1; i >= 0 && s[i] == ' '; i++) {
		end = i;
	}
	len = 0;
	for (long long i = start; i <= end; i++) {
		if (s[i] == ' ' && s[i - 1] == ' ') {
			continue;
		}
		s[len++] = s[i];
	}
	s.erase(s.begin() + len, s.end());
	reverse(s.begin(), s.end());
	start = 0;
	for (long long i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			reverse(s.begin() + start, s.begin() + i);
			start = i + 1;
		}
	}
	reverse(s.begin() + start, s.end());
	if (s[s.length() - 1] == ' ') {
		for (long long i = 1; i < s.length(); i++) {
			cout << s[i];
		}
		cout << endl;
	}
	else {
		cout << s << endl;
	}
	return 0;
}