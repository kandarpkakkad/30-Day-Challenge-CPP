#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/roman-to-integer/
	https://leetcode.com/problems/integer-to-roman/

	Input:
	LVIII
	1994

*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	int rn;
	cin >> s >> rn;

	// Method 1 (Roman to Integer):
	// We create map for character to number and add and subtract the desired output to answer.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	unordered_map<char, int> mp = {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000}
	};
	long long sum = mp[s.back()];
	for (long long i = s.length() - 2; i >= 0; i--) {
		if (mp[s[i]] < mp[s[i + 1]]) {
			sum -= mp[s[i]];
		}
		else {
			sum += mp[s[i]];
		}
	}
	cout << sum << endl;

	// Method 1 (Integer to Roman):
	// We store the possible conversions in array and find the indexes for conversion of number to string.
	// Time Complexity: O(1)
	// Space Complexity: O(1)
	string M[] = {"", "M", "MM", "MMM"};
	string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
	cout << M[rn / 1000] + C[(rn % 1000) / 100] + X[(rn % 100) / 10] + I[(rn % 10)] << endl;
	return 0;
}