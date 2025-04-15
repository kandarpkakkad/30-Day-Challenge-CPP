#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/palindrome-partitioning

	Input:
	aabaa

	Output:
	a a b a a
	a a b aa
	a aba a
	aa b a a
	aa b aa
	aabaa
*/

bool is_palin(const string &s, long long start, long long end) {
	while (start <= end) {
		if (s[start++] != s[end--]) {
			return false;
		}
	}
	return true;
}

void solve(long long index, string &s, vector<string> &path, vector<vector<string>> &ans) {
	if (index == s.size()) {
		ans.push_back(path);
		return;
	}
	for (long long i = index; i < s.size(); i++) {
		if (is_palin(s, index, i)) {
			path.push_back(s.substr(index, i - index + 1));
			solve(i + 1, s, path, ans);
			path.pop_back();
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

	// Method 1:
	// We will every partition and check if it is palindrome or not.
	// Time Complexity: O()
	// Space Complexity: O()
	vector<vector<string>> ans;
	if (s.empty()) {
		cout << "Empty String" << endl;
	}
	else {
		vector<string> path;
		solve(0, s, path, ans);
		for (long long i = 0; i < ans.size(); i++) {
			for (long long j = 0; j < ans[i].size(); j++) {
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}