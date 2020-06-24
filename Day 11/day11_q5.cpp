#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/

	Input:
	6 7 12
	1 2 3 4 5 6
	4 5 6 7 8 9 10

	Output:
	9
	9
	9
	9
*/

long long kth1(long long *arr1, long long *arr2, long long *end1, long long *end2, long long k) {
	if (arr1 == end1) {
		return arr2[k - 1];
	}
	if (arr2 == end2) {
		return arr1[k - 1];
	}
	long long mid1 = (end1 - arr1) / 2;
	long long mid2 = (end2 - arr2) / 2;
	if (mid1 + mid2 < k) {
		if (arr1[mid1] > arr2[mid2]) {
			return kth1(arr1, arr2 + mid1 + 1, end1, end2, k - mid2 - 1);
		}
		else {
			return kth1(arr1 + mid1 + 1, arr2, end1, end2, k - mid1 - 1);
		}
	}
	else {
		if (arr1[mid1] > arr2[mid2]) {
			return kth1(arr1, arr2, arr1 + mid1, end2, k);
		}
		else {
			return kth1(arr1, arr2, end1, arr2 + mid2, k);
		}
	}
}

long long kth2(long long arr1[], long long arr2[], long long N, long long M, long long k, long long st1 = 0, long long st2 = 0) {
	if (st1 == N) {
		return arr2[st2 + k - 1];
	}
	if (st2 == M) {
		return arr1[st1 + k - 1];
	}
	if (k == 0 || k > (N - st1) + (M - st2)) {
		return -1;
	}
	if (k == 1) {
		return (arr1[st1] < arr2[st2]) ? arr1[st1] : arr2[st2];
	}
	long long curr = k / 2;
	if (curr - 1 >= N - st1) {
		if (arr1[N - 1] < arr2[st2 + curr - 1]) {
			return arr2[st2 + (k - (N - st1) - 1)];
		}
		else {
			return kth2(arr1, arr2, N, M, k - curr, st1, st2 + curr);
		}
	}
	if (curr - 1 >= M - st2) {
		if (arr2[M - 1] < arr1[st1 + curr - 1]) {
			return arr1[st1 + (k - (M - st2) - 1)];
		}
		else {
			return kth2(arr1, arr2, N, M, k - curr, st1 + curr, st2);
		}
	}
	else {
		if (arr1[curr + st1 - 1] < arr2[curr + st2 - 1]) {
			return kth2(arr1, arr2, N, M, k - curr, st1 + curr, st2);
		}
		else {
			return kth2(arr1, arr2, N, M, k - curr, st1, st2 + curr);
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, k;
	cin >> N >> M >> k;
	long long arr1[N], arr2[M];
	for (long long i = 0; i < N; i++) {
		cin >> arr1[i];
	}
	for (long long i = 0; i < M; i++) {
		cin >> arr2[i];
	}

	// Method 1:
	// We are given sorted arrays and so we merge the array and find the kth element.
	// Time Complexity: O(n)
	// Space Complexity: O(m + n)
	long long sorted[N + M];
	long long i = 0, j = 0, d = 0;
	while (i < N && j < M) {
		if (arr1[i] < arr2[j]) {
			sorted[d++] = arr1[i++];
		}
		else {
			sorted[d++] = arr2[j++];
		}
	}
	while (i < N) {
		sorted[d++] = arr1[i++];
	}
	while (j < M) {
		sorted[d++] = arr2[j++];
	}
	cout << sorted[k - 1] << endl;

	// Method 2:
	// Now instead of extra space, we use 2 pointers to find kth element.
	// Time Complexity: O(k)
	// Space Complexity: O(1)
	long long l = 0;
	i = 0, j = 0;
	while (i < N && j < M) {
		if (arr1[i] < arr2[j]) {
			l++;
			if (l == k) {
				cout << arr1[i] << endl;
				i = N - 1;
				j = M - 1;
				break;
			}
			i++;
		}
		else {
			l++;
			if (l == k) {
				cout << arr2[j] << endl;
				i = N - 1;
				j = M - 1;
				break;
			}
			j++;
		}
	}
	while (i < N) {
		l++;
		if (l == k) {
			cout << arr1[i] << endl;
			i = N - 1;
			j = M - 1;
			break;
		}
		i++;
	}
	while (j < M) {
		l++;
		if (l == k) {
			cout << arr2[j] << endl;
			i = N - 1;
			j = M - 1;
			break;
		}
		j++;
	}

	// Method 3:
	// Divide and Conquer. Explanation: We compare the middle elements of arrays arr1 and arr2, let us call these indices mid1 and mid2 respectively. Let us assume arr1[mid1]  k, then clearly the elements after  mid2 cannot be the required element. We then set the last element of arr2 to be arr2[mid2]. In this way, we define a new subproblem with half the size of one of the arrays.
	// Time Complexity: O(log(n) + log(m))
	// Space Complexity: O(1)
	cout << kth1(arr1, arr2, arr1 + N, arr2 + M, k) << endl;

	// Method 4:
	// Divide and Conquer again. Instead of comparing the middle element of the arrays, we compare the k / 2nd element.
	// Time Complexity: O(log(k))
	// Space Complexity: O(1)
	cout << kth2(arr1, arr2, N, M, k);
	return 0;
}