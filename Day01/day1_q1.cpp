#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/find-the-duplicate-number/

	Input:
	6
	1 2 2 5 3 3

	Output:
	2
	2
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// We count the frequency of the numbers present the array and the first number with frequency = 2 is the answer.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	bool flag = false;
	long long ans = -1;
	long long cnt[100005] = {0};
	for (long long i = 0; i < N; i++) {
		if (cnt[arr[i]] == 1) {
			flag = true;
			ans = arr[i];
			break;
		}
		cnt[arr[i]]++;
	}
	cout << ans << endl;

	// Method 2:
	// Race pointers: Just like finding middle element in linked list, we loop in the traversal to find the repeating element. Once that is done now we keep that loop while we traverse the original array and if the both the elements are true at any time, that is the answer.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long x = arr[0], y = arr[0];
	do {
		x = arr[x];
		y = arr[arr[y]];
	} while (x != y);
	x = arr[0];
	while (x != y) {
		x = arr[x];
		y = arr[y];
	}
	cout << x << endl;
	return 0;
}