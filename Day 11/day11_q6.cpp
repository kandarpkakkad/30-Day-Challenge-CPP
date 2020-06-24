#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/

	Intput:
	6 7
	1 2 3 4 5 6
	4 5 6 7 8 9 10

	Output:
	5
	5
*/

double median2(long long a, long long b) {
	return (a + b) / 2.0;
}

double median3(long long a, long long b, long long c) {
	return a + b + c - max(a, max(b, c)) - min(a, min(b, c));
}

double median4(long long a, long long b, long long c, long long d) {
	long long mx = max(a, max(b, max(c, d)));
	long long mn = min(a, min(b, min(c, d)));
	return (a + b + c + d - mx - mn) / 2.0;
}

double median_single_array(long long arr[], long long N) {
	if (N == 0) {
		return -1;
	}
	if (N % 2 == 0) {
		return (double)(arr[N / 2] + arr[N / 2 - 1]) / 2;
	}
	return arr[N / 2];
}

double find_median(long long arr1[], long long arr2[], long long N, long long M) {
	if (N == 0) {
		return median_single_array(arr2, M);
	}
	if (N == 1) {
		if (M == 1) {
			return median2(arr1[0], arr2[0]);
		}
		if (M % 2 == 1) {
			return median2(arr2[M / 2], median3(arr1[0], arr2[M / 2 - 1], arr2[M / 2 + 1]));
		}
		return median3(arr2[M / 2], arr2[M / 2 - 1], arr1[0]);
	}
	else if (N == 2) {
		if (M == 2) {
			return median4(arr1[0], arr1[1], arr2[0], arr2[1]);
		}
		if (M % 2 == 1) {
			return median3(arr2[M / 2], max(arr1[0], arr2[M / 2 - 1]), min(arr1[1], arr2[M / 2 + 1]));
		}
		return median4(arr2[M / 2], arr2[M / 2 - 1], max(arr1[0], arr2[M / 2 - 2]), min(arr1[1], arr2[M / 2 + 1]));
	}
	long long idxarr1 = (N - 1) / 2;
	long long idxarr2 = (M - 1) / 2;
	if (arr1[idxarr1] <= arr2[idxarr2]) {
		return find_median(arr1 + idxarr1, arr2, N / 2 + 1, M - idxarr1);
	}
	return find_median(arr1, arr2 + idxarr1, N / 2 + 1, M - idxarr1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long arr1[N], arr2[M];
	for (long long i = 0; i < N; i++) {
		cin >> arr1[i];
	}
	for (long long i = 0; i < M; i++) {
		cin >> arr2[i];
	}

	// Method 1:
	// We merge the the sorted arrat and (M + N) / 2th element.
	// Time Complexity: O(m+n)
	// Space Complexity: O(1)
	long long i = 0, j = 0, count, m1 = -1, m2 = -1;
	if ((N + M) % 2 == 1) {
		for (count = 0; count <= (N + M) / 2; count++) {
			if (i != N && j != M) {
				m1 = (arr1[i] > arr2[j]) ? arr2[j++] : arr1[i++];
			}
			else if (i < N) {
				m1 = arr1[i++];
			}
			else {
				m1 = arr2[j++];
			}
		}
		cout << m1 << endl;
	}
	else {
		for (count = 0; count <= (N + M) / 2; count++) {
			m2 = m1;
			if (i != N && j != M) {
				m1 = (arr1[i] > arr2[j]) ? arr2[j++] : arr1[i++];
			}
			else if (i < N) {
				m1 = arr1[i++];
			}
			else {
				m1 = arr2[j++];
			}
		}
		cout << (m1 + m2) / 2 << endl;
	}

	// Method 2:
	// Divide and Conquer. The idea is simple, calculate the median of both the arrays and discard one half of each array.
	// Time Complexity: O(min(log(m), log(n)))
	// Space Complexity: O(1)
	if (N > M) {
		cout << find_median(arr2, arr1, M, N) << endl;
	}
	else {
		cout << find_median(arr1, arr2, N, M) << endl;
	}
	return 0;
}