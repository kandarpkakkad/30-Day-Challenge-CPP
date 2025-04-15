#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/word-break/

	Input:
	applepenapple
	2
	apple
	pen

	Output:
	Yes
	Yes
	Yes
*/

bool dfs(string s, unordered_set<string> dict, unordered_set<string> vis) {
	if (s.empty()) {
		return true;
	}
	if (vis.find(s) != vis.end()) {
		return false;
	}
	vis.insert(s);
	for (auto str : dict) {
		if (s.rfind(str, 0) == 0 && dfs(s.substr(str.length()), dict, vis)) {
			return true;
		}
	}
	return false;
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
	unordered_set<string> dict;
	string temp;
	for (long long i = 0; i < N; i++) {
		cin >> temp;
		dict.insert(temp);
	}

	// Method 1:
	// Idea is to try to chop off prefix of s that is in the dict enqueue the left-over of each chop off. If there is a time the left over happens to be in the dict as well we know word is breakable, b/c all the previous chops are all in the dict otherwise the original world is not breakable. We can use a set to store all the leftovers that we have tried, to avoid enqueue the same leftover multiple times.
	// Time Complexity: O()
	// Space Complexity: O()
	long long ind = 0;
	queue<string> q;
	q.push(s);
	unordered_set<string> vis;
	bool flag = false;
	while (!q.empty()) {
		string candidate = q.front();
		q.pop();
		if (dict.find(candidate) != dict.end()) {
			flag = true;
			break;
		}
		for (long long i = 0; i < candidate.length(); i++) {
			string prev = candidate.substr(0, i);
			string post = candidate.substr(i, candidate.length());
			if (vis.find(post) == vis.end() && dict.find(prev) != dict.end());
			q.push(post);
			vis.insert(post);
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// We use a boolean vector dp[]. dp[i] is set to true if a valid word (word sequence) ends there. The optimization is to look from current position i back and only substring and do dictionary look up in case the preceding position j with dp[j] == true is found.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	vector<bool> dp(s.size() + 1, false);
	dp[0] = true;
	for (long long i = 1; i < s.size() + 1; i++) {
		for (long long j = i - 1; j >= 0; j--) {
			if (dp[j] == true) {
				string word = s.substr(j, i - j);
				if (dict.find(word) != dict.end()) {
					dp[i] = true;
					break; // for next i.
				}
			}
		}
	}
	if (dp[s.size()]) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 3:
	// Straightforward DFS solution, the only trick is to memorize already checked strings.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2) (recursive stack)
	unordered_set<string> vis2;
	if (dfs(s, dict, vis2)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}