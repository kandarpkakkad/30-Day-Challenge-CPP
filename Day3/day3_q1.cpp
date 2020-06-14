#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string inp;
	cin >> inp;

	// Method 1:
	// We multiply each of the character's position in alphabet by 26 for N - 1 characters in string and add the last character's postition in alphabets.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long ans = 0;
	for (long long i = 0; i < inp.length() - 1; i++) {
		ans += (inp[i] - 'A' + 1) * 26;
	}
	ans += (inp[inp.length() - 1] - 'A' + 1);
	cout << ans << endl;
	return 0;
}