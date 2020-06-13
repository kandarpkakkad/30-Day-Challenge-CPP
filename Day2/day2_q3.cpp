#include<bits/stdc++.h>

using namespace std;

void swap(long long &a, long long &b) {
	long long t = a;
	a = b;
	b = t;
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
	// Find i such that for all k > i arr[i] > arr[k].
	// Find j > i such that for all k >= j arr[k] <= arr[i - 1]
	// swap arr[i] and arr[j]
	// swap all the values from i to j.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long i = N - 1;
	while (i > 0 && arr[i - 1] >= arr[i]) {
		i--;
	}
	if (i <= 0) {
		cout << "This is last permutation.";
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
		for (long long i = 0; i < N; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	return 0;
}