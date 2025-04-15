#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

	Input:
	6
	7 1 5 3 6 4

	Output:
	5
	5
	5
	5
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
	// We will find maximum number occuring after the number for each number in the array.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	long long mx = LLONG_MIN;
	for (long long i = 0; i < N; i++) {
		for (long long j = i + 1; j < N; j++) {
			if (arr[i] < arr[j]) {
				mx = max(mx, arr[j] - arr[i]);
			}
		}
	}
	cout << mx << endl;

	// Method 2:
	// Here we will do the same thing but in O(n) time.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long mn = arr[0];
	mx = arr[0];
	for (long long i = 1; i < N; i++) {
		if (arr[i] < mn) {
			mn = arr[i];
			mx = arr[i];
		}
		if (arr[i] > mx) {
			mx = arr[i];
		}
	}
	cout << mx - mn << endl;

	// Method 3:
	// By deque, we will find such numbers before whom there is no smaller number then them.
	// After that we will check the maximum number after the index for which we are checking.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	deque<pair<long long, long long>> dq;
	long long ans = 0;
	for (long long i = 1; i < N; i++) {
		if (dq.empty()) {
			dq.push_back({arr[i], i});
		}
		else {
			while (!dq.empty() && dq.back().first < arr[i]) {
				dq.pop_back();
			}
			dq.push_back({arr[i], i});
		}
		// for (long long i = 0; i < dq.size(); i++) {
		// 	cout << dq[i].first << " - " << dq[i].second << endl;
		// }
		// cout << endl;
	}
	for (long long i = 0; i < N; i++) {
		if (i == dq.front().second) {
			dq.pop_front();
		}
		else {
			ans = max(ans, dq.front().first - arr[i]);
		}
	}
	cout << ans << endl;

	// Method 4:
	// Dynamic Programming with Kadane's algorithm.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long max_curr = 0, max_so_far = 0;
	for (long long i = 1; i < N; i++) {
		max_curr = max((long long)0, max_curr + (arr[i] - arr[i - 1]));
		max_so_far = max(max_curr, max_so_far);
	}
	cout << max_so_far << endl;
	return 0;
}