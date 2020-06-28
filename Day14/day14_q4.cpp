#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/sliding-window-maximum/

	Input:
	6 2
	2 1 5 6 2 3

	Output:
	2 5 6 6 3
	2 5 6 6 3
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// Using deque to find the maximum in subarray of length k. When the larger element comes or i - k + 1 is present in the deque, we pop them out to satisfy our condition.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	deque<long long> dq;
	vector<long long> ans;
	for (long long i = 0; i < N; i++) {
		if (!dq.empty() && dq.front() == i - k) {
			dq.pop_front();
		}
		while (!dq.empty() && arr[dq.back()] < arr[i]) {
			dq.pop_back();
		}
		dq.push_back(i);
		if (i >= k - 1) {
			ans.push_back(arr[dq.front()]);
		}
	}
	for (long long i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

	// Method 2:
	// Instead of deque we will use priority queue but the logic remains same.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n)
	ans.clear();
	priority_queue<pair<long long, long long>> pq;
	for (long long i = 0; i < N; i++) {
		while (!pq.empty() && pq.top().second <= i - k) {
			pq.pop();
		}
		pq.push(make_pair(arr[i], i));
		if (i >= k - 1) {
			ans.push_back(pq.top().first);
		}
	}
	for (long long i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}