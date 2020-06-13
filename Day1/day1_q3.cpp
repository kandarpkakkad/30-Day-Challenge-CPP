#include<bits/stdc++.h>

using namespace std;

long long binary_search(long long arr[], long long N) {
	long long ans = -1;
	long long beg = 0;
	long long end = N - 1;
	long long mid;
	while (beg < end) {
		mid = (beg + end) / 2;
		if (arr[mid] == mid) {
			beg = mid + 1;
		}
		else {
			end = mid + 1;
		}
	}
	ans = beg;
	if (arr[ans] == ans) {
		ans = -1;
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	// Missing Number
	// You need to find the missing number from 0 to N.
	long long N;
	cin >> N;
	long long arr[N + 1];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// Sum of N numbers - Sum of numbers in array
	long long expected = N * (N + 1) / 2;
	long long sum = 0;
	for (long long i = 0; i < N; i++) {
		sum += arr[i];
	}
	cout << expected - sum << endl;

	// Method 2:
	// XOR of all the elements in the array
	long long ans = 0;
	long long temp = 0;
	for (long long i = 0; i < N; i++) {
		ans = ans ^ arr[i];
		temp = temp ^ i;
	}
	temp = temp ^ N;
	ans = ans ^ temp;
	cout << ans << endl;

	// Method 3;
	// Binary search to find the missing number.
	// In binary search, we will check if the value of array at index mid is mid. If not we go left, otherwise right.
	sort(arr, arr + N);
	ans = binary_search(arr, N);
	if (ans == -1) {
		cout << N << endl;
	}
	else {
		cout << ans << endl;
	}
	return 0;
}