#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/kth-largest-element-in-an-array/

	You need to run the methods separately.

	Input:
	9 4
	3 2 3 1 2 4 5 5 6

	Output:
	4th smallest number:3
	4th largest number:4

	4th smallest number:3
	4th largest number:4

	4th smallest number:3
	4th largest number:4

	4th smallest number:3
	4th largest number:4

	4th smallest number:3
	4th largest number:4

	4th smallest number:3
	4th largest number:4
*/

void swap(long long &a, long long &b) {
	long long t = a;
	a = b;
	b = t;
}

long long partition_largest(long long arr[], long long left, long long right) {
	long long pivot = arr[left], l = left + 1, r = right;
	while (l <= r) {
		if (arr[l] < pivot && arr[r] > pivot) {
			swap(arr[l++], arr[r--]);
		}
		if (arr[l] >= pivot) {
			l++;
		}
		if (arr[r] <= pivot) {
			r--;
		}
	}
	swap(arr[left], arr[r]);
	return r;
}

long long kth_largest(long long arr[], long long N, long long k) {
	long long left = 0, right = N - 1, kth;
	while (true) {
		long long idx = partition_largest(arr, left, right);
		if (idx == k - 1) {
			kth = arr[idx];
			break;
		}
		if (idx < k - 1) {
			left = idx + 1;
		}
		else {
			right = idx - 1;
		}
	}
	return kth;
}

long long partition_smallest(long long arr[], long long left, long long right) {
	long long pivot = arr[left], l = left + 1, r = right;
	while (l <= r) {
		if (arr[l] > pivot && arr[r] < pivot) {
			swap(arr[l++], arr[r--]);
		}
		if (arr[l] <= pivot) {
			l++;
		}
		if (arr[r] >= pivot) {
			r--;
		}
	}
	swap(arr[left], arr[r]);
	return r;
}

long long kth_smallest(long long arr[], long long N, long long k) {
	long long left = 0, right = N - 1, kth;
	while (true) {
		long long idx = partition_smallest(arr, left, right);
		if (idx == k - 1) {
			kth = arr[idx];
			break;
		}
		if (idx < k - 1) {
			left = idx + 1;
		}
		else {
			right = idx - 1;
		}
	}
	return kth;
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
	// Simple method. Sort the array and print kth element.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	sort(arr, arr + N);
	cout << k << "th smallest number: " << arr[k - 1] << endl;
	cout << k << "th largest number:" << arr[N - k] << endl;

	// Method 2:
	// We will use partial sorting. STL has 2 functions: nth_element & partial_sort.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	partial_sort(arr, arr + k - 1, arr + N);
	cout << k << "th smallest number: " << arr[k - 1] << endl;
	cout << k << "th largest number:" << arr[N - k] << endl;
	// OR
	nth_element(arr, arr + k, arr + N);
	cout << k << "th smallest number: " << arr[k - 1] << endl;
	cout << k << "th largest number:" << arr[N - k] << endl;

	// Method 3:
	// We will solve using min-heap and max-heap. We will maintain the smallest and largest elemets with largest and smallest among them at the top.
	// Time Complexity: O(klog(k))
	// Space Complexity: O(k)
	priority_queue<long long, vector<long long>, greater<long long>> pq;
	for (long long i = 0; i < N; i++) {
		pq.push(arr[i]);
		if (pq.size() > N - k) {
			pq.pop();
		}
	}
	cout << k << "th smallest number:" << pq.top() << endl;
	while (pq.size()) {
		pq.pop();
	}
	for (long long i = 0; i < N; i++) {
		pq.push(arr[i]);
		if (pq.size() > k) {
			pq.pop();
		}
	}
	cout << k << "th largest number:" << pq.top() << endl;
	// OR
	priority_queue<long long> pq2(arr, arr + N);
	for (long long i = 0; i < N - k - 1; i++) {
		pq2.pop();
	}
	cout << k << "th smallest number:" << pq2.top() << endl;
	priority_queue<long long> pq(arr, arr + N);
	for (long long i = 0; i < k - 1; i++) {
		pq.pop();
	}
	cout << k << "th largest number:" << pq.top() << endl;

	// Method 4:
	// We use partial partitioning of quicksort to find the kth largest and smallest element;
	// Time Complexity: O(n^2), Ɵ(n)
	// Space Complexity: O(1)
	cout << k << "th smallest number: " << kth_smallest(arr, N, k) << endl;
	cout << k << "th largest number:" << kth_largest(arr, N, k) << endl;
	return 0;
}