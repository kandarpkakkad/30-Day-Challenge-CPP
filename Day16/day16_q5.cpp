#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/count-and-say

	Input:
	12

	Output:
	3113112221232112111312211312113211
	3113112221232112111312211312113211
*/

string cnt_and_say(long long n) {
	if (n == 1) {
		return "1";
	}
	if (n == 2) {
		return "11";
	}
	string result = cnt_and_say(n - 1);
	string new_result = "";
	long long cnt = 1;
	for (long long i = 1; i < result.length(); i++) {
		if (result[i] != result[i - 1]) {
			new_result.push_back('0' + cnt);
			new_result.push_back(result[i - 1]);
			cnt = 1;
		}
		else {
			cnt++;
		}
		if (i == result.length() - 1) {
			new_result.push_back('0' + cnt);
			new_result.push_back(result[i]);
		}
	}
	return new_result;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long M = N;

	// Method 1:
	// We will count each time the consecutive numbers and add the count of that number changing the answer everytime.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	if (N == 0) {
		cout << "" << endl;
	}
	else {
		string ans = "1";
		while (--N) {
			string curr = "";
			for (long long i = 0; i < ans.size(); i++) {
				long long cnt = 1;
				while ((i + 1 < ans.size()) && (ans[i] == ans[i + 1])) {
					cnt++;
					i++;
				}
				curr += to_string(cnt) + ans[i];
			}
			ans = curr;
		}
		cout << ans << endl;
	}

	// Method 2:
	// Now we will use recursion instead of iterative method.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	string ans = cnt_and_say(M);
	cout << ans << endl;
	return 0;
}