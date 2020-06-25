#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/search-in-rotated-sorted-array/

	Input:
	7
	4 5 6 7 1 2 3

	Output:
	Position = 5
*/

long long bs(long long arr[], long long N, long long x) {
	long long start = 0;
	long long end = N - 1;
	long long mid;
	while (start < end) {
		mid = (start + end) / 2;
		if (arr[mid] > arr[end]) {
			start = mid + 1;
		}
		else {
			end = mid;
		}
	}
	long long rotate = start;
	start = 0;
	end = N - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		long long rmid = (mid + rotate) % N;
		if (arr[rmid] == x) {
			return rmid;
		}
		if (arr[rmid] < x) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return -1;
}

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
	// Binary search
	// Time Complexity: O(log(n))
	// Space Complexity: O(1)
	long long ans = bs(arr, N, 1);
	if (ans == -1) {
		cout << "No Solution" << endl;
	}
	else {
		cout << "Position = " << ans + 1 << endl;
	}
	return 0;
}