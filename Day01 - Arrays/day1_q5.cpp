#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/maximum-subarray

	Input:
	6
	-1 0 1 -2 4 5

	Output:
	Starting: 5	Ending: 6
	9
	9
*/

long long max_mid_sub_array(long long arr[], long long l, long long mid, long long r) {
	// Now we will find maximum sum from mid to left
	long long sum = 0;
	long long max_left = LLONG_MIN;
	for (long long i = mid; i >= l; i--) {
		sum += arr[i];
		if (sum > max_left) {
			max_left = sum;
		}
	}

	// Now we will find maximum sum from mid to right
	sum = 0;
	long long max_right = LLONG_MIN;
	for (long long i = mid + 1; i <= r; i++) {
		sum += arr[i];
		if (sum > max_right) {
			max_right = sum;
		}
	}
	return max(max(max_left + max_right, max_left), max_right);
}

long long max_sub_array(long long arr[], long long l, long long r) {
	if (l == r) {
		return arr[l];
	}
	long long mid = (l + r) / 2;
	return max(
	           max(
	               max_sub_array(arr, l, mid),
	               max_sub_array(arr, mid + 1, r)
	           ),
	           max_mid_sub_array(arr, l, mid, r)
	       );
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
	// What we will do is add the element one by one to the sum and if sum if less than 0 we will store the maximum sum yet to final answer and make sum = 0 for the remaining elements.
	// This is called Kadane's Algorithm
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long max_global = LLONG_MIN; // final ans
	long long max_local = 0; // check maximum sum of all possible subarrays
	long long start = -1; // starting of maximal sum subarray
	long long end = -1; // ending of maximal sum subarray
	long long s = 0; // to find the starting of all subarrays
	for (long long i = 0; i < N; i++) {
		max_local += arr[i];
		if (max_global < max_local) {
			max_global = max_local;
			start = s;
			end = i;
		}
		if (max_local < 0) {
			max_local = 0;
			s = i + 1;
		}
	}
	cout << "Starting: " << start + 1 << "\tEnding: " << end + 1 << endl;
	cout << max_global << endl;

	// Method 2:
	// Now we are going to try something different i.e. Divide and Conquer. But here we won't get the staring and ending index of the maximal sum subarray.
	// What we will do is divide the array into 2 parts and find maximum sums of it and find maximum sum of left from mid and right from mid and add it and then take maximum of the three.
	// Time Complexity: O(n*log(n))
	// Space Complexity: O(log(n)) i.e. the stack of recursion
	long long ans = max_sub_array(arr, 0, N - 1);
	cout << ans << endl;
	return 0;
}