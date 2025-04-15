#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/merge-sorted-array/

	Input:
	6 4
	0 1 3 4 5 6
	2 7 8 9

	Output:
	0 1 2 3 4 5 6 7 8 9
	0 1 2 2 3 4 5 7 8 9
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long arr1[N + M], arr2[N + M];
	for (long long i = 0; i < N; i++) {
		cin >> arr1[i];
	}
	for (long long i = 0; i < M; i++) {
		cin >> arr2[i];
	}

	// Method 1:
	// We will use 3 pointers one pointing at greatest value of array1 and another at greatest value of array2 and we will decreament the pointer if the value at that pointer is greater than the other pointer. The third pointer is where the greatest value from the two is stored in array1.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long final_pos = N + M - 1;
	long long pos1 = N - 1;
	long long pos2 = M - 1;
	while (pos1 >= 0 && pos2 >= 0) {
		if (arr1[pos1] > arr2[pos2]) {
			arr1[final_pos--] = arr1[pos1--];
		}
		else {
			arr1[final_pos--] = arr2[pos2--];
		}
	}
	while (pos2 >= 0) {
		arr1[final_pos--] = arr2[pos2--];
	}
	for (long long i = 0; i < N + M; i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;

	// Method 2:
	// Simple method. Add the elements of array2 to array1 and sort it.
	// Time Complexity: O(n*log(n))
	// Space Complexity: O(1)
	for (long long i = N; i < N + M; i++) {
		arr1[i] = arr2[i - N];
	}
	sort(arr1, arr1 + N + M - 1);
	for (long long i = 0; i < N + M; i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;
	return 0;
}