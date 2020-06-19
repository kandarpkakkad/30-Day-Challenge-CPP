#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	long long N = s.length();

	// Method 1:
	// We create a set for characters and if we find the character in the set we remove the charater from the set and increament the starting position else increament the ending position and add the new element in the set.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	unordered_set<char> st;
	long long i = 0, j = 0;
	long long ans = 0;
	while (i < N && j < N) {
		if (st.find(s[j]) == st.end()) {
			st.insert(s[j]);
			j++;
			ans = max(ans, j - i);
		}
		else {
			st.erase(s[i]);
			i++;
		}
	}
	cout << ans << endl;

	// Method 2:
	// Sliding Window. Traverse and search the string for repeatation.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n)
	ans = 0;
	long long start = 0, temp = 0, temp_sub = 0;
	for (long long i = 0; i < N; i++) {
		temp = s.find(s.at(i), start); // search for duplicates
		if (temp != i) {
			start = temp + 1;
		}
		temp_sub = i - start + 1;
		if (ans < temp_sub) {
			ans = temp_sub;
		}
	}
	cout << ans << endl;
	return 0;
}