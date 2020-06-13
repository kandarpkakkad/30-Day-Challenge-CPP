#include<bits/stdc++.h>

using namespace std;

long long merge(long long arr[], long long temp[], long long left, long long mid, long long right) {
	long long l, m, k;
	long long inversions = 0;
	l = left;
	m = mid;
	k = left;
	while ((l <= mid - 1) && (m <= right)) {
		if (arr[l] <= arr[m]) {
			temp[k++] = arr[l++];
		}
		else {
			temp[k++] = arr[m++];
			inversions += (mid - l);
		}
	}
	while (l <= mid - 1) {
		temp[k++] = arr[l++];
	}
	while (m <= right) {
		temp[k++] = arr[m++];
	}
	for (l = left; l <= right; l++) {
		arr[l] = temp[l];
	}
	return inversions;
}

long long merge_sort(long long arr[], long long temp[], long long left, long long right) {
	long long mid, inversions = 0;
	if (right > left) {
		mid = (right + left) / 2;
		inversions += merge_sort(arr, temp, left, mid);
		inversions += merge_sort(arr, temp, mid + 1, right);
		inversions += merge(arr, temp, left, mid + 1, right);
	}
	return inversions;
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
	// We will count all the numbers less the current number on the right and the current number will all the numbers.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	long long cnt = 0;
	for (long long i = 0; i < N; i++) {
		for (long long j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				cnt++;
			}
		}
	}
	cout << cnt << endl;

	// Method 2:
	// We will divide array into 2 parts and find inversions in both the parts and inversions between left and right and add it to find total number of inversions.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n)
	long long temp[N];
	long long ans = merge_sort(arr, temp, 0, N - 1);
	cout << ans << endl;
	return 0;
}