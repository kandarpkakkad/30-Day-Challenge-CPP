#include<bits/stdc++.h>

using namespace std;

/*
	https://www.interviewbit.com/problems/distinct-numbers-in-window/

	Input:
	7 4
	1 2 1 3 4 2 3

	Output:
	3 4 4 3
	3 4 4 3
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
	// Naive approach is to traverse the given array considering every window in it and keeping a count on the distinct numbers in it.
	// Time Complexity: O(nk^2)
	// Space Complexity: O(1)
	for (long long i = 0; i <= N - k; i++) {
		long long cnt = 0;
		for (long long j = i; j < i + k; j++) {
			long long l;
			for (l = i; l < i + j; l++) {
				if (arr[j] == arr[l]) {
					break;
				}
			}
			if (j == l) {
				cnt++;
			}
		}
		cout << cnt << " ";
	}
	cout << endl;

	// Method 2:
	// We use similar approach but we auxiliary space as well to decrease the time complexity. We will use hash map to store the elements in a window and when the window changes we dont calculate from beginning but rather remove first element and add a new element and calculate again.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	map<long long, long long> hash;
	long long cnt = 0;
	for (long long i = 0; i < k; i++) {
		if (hash[arr[i]] == 0) {
			cnt++;
		}
		hash[arr[i]]++;
	}

	cout << cnt << " ";
	for (long long i = k; i < N; i++) {
		if (hash[arr[i - k]] == 1) {
			cnt--;
		}
		hash[arr[i - k]] -= 1;
		if (hash[arr[i]] == 0) {
			cnt++;
		}
		hash[arr[i]]++;
		cout << cnt << " ";
	}
	cout << endl;
	return 0;
}