#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/sort-colors/

	Input:
	6
	1 0 2 0 1 2

	Output:
	0 0 1 1 2 2
	0 0 1 1 2 2
*/

void swap(long long &a, long long &b) {
	long long t = a;
	a = b;
	b = t;
}

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
	// What we are going to do is keep 3 pointers for 0, 2 and current position.
	// The pointer for 0 will point to minimum of current position and leftmost place after 0.
	// The pointer for 2 will point to maximum of current position and rightmost place before 2.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long r0 = 0;
	long long l2 = N - 1;
	long long curr = 0;
	while (curr <= l2) {
		if (arr[curr] == 0) {
			swap(arr[r0], arr[curr]);
			r0++;
			curr++;
		}
		else if (arr[curr] == 2) {
			swap(arr[l2], arr[curr]);
			l2--;
		}
		else {
			curr++;
		}
	}
	for (long long i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	// Method 2:
	// Simple method. We will sort 0s first ans 1s later and then 2 will be sorted already.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long x = -1;
	for (long long y = 0; y < N; y++) {
		if (arr[y] == 0) {
			swap(arr[++x], arr[y]);
		}
	}
	long long z = x;
	for (long long y = x; y < N; y++) {
		if (arr[y] == 1) {
			swap(arr[++z], arr[y]);
		}
	}
	for (long long i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}