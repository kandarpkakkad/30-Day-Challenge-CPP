#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/permutation-sequence/

	Input:
	3 5

	Output:
	3 1 2
*/

void swap(long long &a, long long &b) {
	long long t = a;
	a = b;
	b = t;
}

bool next_perm(long long *arr, long long N) {
	long long i = N - 1;
	while (i > 0 && arr[i - 1] >= arr[i]) {
		i--;
	}
	if (i <= 0) {
		return false;
	}
	else {
		long long j = N - 1;
		while (arr[j] <= arr[i - 1]) {
			j--;
		}
		swap(arr[i - 1], arr[j]);
		j = N - 1;
		while (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
		return true;
	}
}

void kth_perm(long long *arr, long long N, long long k) {
	long long i = 1;
	do {
		if (i == k) {
			break;
		}
		i++;
	} while (next_perm(arr, N));
	for (long long i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;

	// Method 1:
	// We find next permutation till count not equal to k.
	// Time Complexity: O(n^2)
	// Space Complexity:O(n)
	long long arr[N];
	iota(arr, arr + N, 1); // makes arr such that arr[i] = m, where m belongs to [1, N].
	kth_perm(arr, N, k);
	return 0;
}