#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/valid-anagram/

	Input:
	anagram
	nagaram
	6
	eat
	tan
	tea
	nat
	ate
	bat

	Output:
	Yes
	Yes
	bat
	tan nat
	eat tea ate
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s1, s2;
	cin >> s1 >> s2;

	// Method 1:
	// We will use count of each character to see whether s2 is anagram of s1.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	if (s1.length() != s2.length()) {
		cout << "No" << endl;
	}
	else {
		long long cnt[26] = {0};
		for (long long i = 0; i < s1.length(); i++) {
			cnt[s1[i] - 'a']++;
			cnt[s2[i] - 'a']--;
		}
		bool flag = true;
		for (long long i = 0; i < 26; i++) {
			if (cnt[i] > 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

	// Method 2:
	// Sorting. We sort both strings and check each character. If they are not same, then they are not anagrams.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	if (s1 == s2) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Another great problem is Grouping Anagrams.
	// https://leetcode.com/problems/group-anagrams/
	long long N;
	cin >> N;
	string arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// We will use unordered map to store the anagrams of a string.
	// Time Complexity: O(n*mlog(m))
	// Space Complexity: O(n)
	unordered_map<string, vector<string>> mp;
	for (long long i = 0; i < N; i++) {
		string t = arr[i];
		sort(t.begin(), t.end());
		mp[t].push_back(arr[i]);
	}
	vector<vector<string>> ans;
	for (auto it : mp) {
		ans.push_back(it.second);
	}
	for (long long i = 0; i < ans.size(); i++) {
		for (long long j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}