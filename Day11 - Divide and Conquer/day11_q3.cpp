#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/find-the-element-that-appears-once-in-a-sorted-array/

	Input:
	11
	1 1 3 3 4 5 5 7 7 9 9

	Output:
	4
*/

void solve(long long arr[], long long start, long long end) {
	if (start > end) {
		cout << "No Solution" << endl;
		return;
	}
	if (start == end) {
		cout << arr[start] << " occurs once." << endl;
		return;
	}
	long long mid = (start + end) / 2;
	if (mid % 2 == 0) {
		if (arr[mid] == arr[mid + 1]) {
			solve(arr, mid + 2, end);
		}
		else {
			solve(arr, start, mid);
		}
	}
	else {
		if (arr[mid] == arr[mid - 1]) {
			solve(arr, mid + 1, end);
		}
		else {
			solve(arr, start, mid - 1);
		}
	}
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
	sort(arr, arr + N);

	// Method 1:
	// Find the middle index, say mid. If mid is even, then compare arr[mid] and arr[mid + 1]. If both are the same, then the required element after mid else before mid. If mid is odd, then compare arr[mid] and arr[mid – 1]. If both are the same, then the required element after mid else before mid.
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	sort(arr, arr + N);
	solve(arr, 0, N - 1);
	return 0;
}