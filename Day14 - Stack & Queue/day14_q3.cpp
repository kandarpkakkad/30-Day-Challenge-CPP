#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/largest-rectangle-in-histogram

	Input:
	6
	2 1 5 6 2 3

	Output:
	10
	10
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long arr[N + 1];
	for (long long i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	arr[0] = 0;
	arr[N + 1] = 0;

	// Method 1:
	// We will use a stack to save the index of each array element in ascending order. Once the current entry is smaller that the one at the top of the stack, then that means calculate rectangle with height at index = top of stack and update the maximum.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	long long ans = 0, index;
	stack<long long> s;
	s.push(0);
	for (long long i = 1; i < N + 2; i++) {
		while (!s.empty() && arr[i] < arr[index = s.top()]) {
			s.pop();
			ans = max(ans, arr[index] * (i - s.top() - 1));
		}
		s.push(i);
	}
	cout << ans << endl;

	// Method 2:
	// DP Method.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	long long p;
	ans = 0;
	vector<long long> left(N + 2, 0), right(N + 2, N);
	for (long long i = 2; i <= N; i++) {
		p = i - 1;
		while (p >= 0 && arr[i] <= arr[p]) {
			p = left[p] - 1;
		}
		left[i] = p + 1;
	}
	for (long long i = N - 1; i >= 1; i--) {
		p = i + 1;
		while (p < N && arr[i] <= arr[p]) {
			p = right[p];
		}
		right[i] = p;
	}
	for (long long i = 1; i < N; i++) {
		ans = max(ans, arr[i] * (right[i] - left[i]));
	}
	cout << ans << endl;
	return 0;
}