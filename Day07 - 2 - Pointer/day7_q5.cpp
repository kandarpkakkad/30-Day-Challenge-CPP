#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/remove-duplicates-from-sorted-array

	Input:
	6
	1 1 2 3 3 4

	Output:
	1 2 3 4
*/

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
	// 1st pointer points to the 2nd position of repeated element and 2nd position will traverse through the array to replace 1st pointer with 2nd pointer.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long ptr1 = 0;
	for (long long ptr2 = 1; ptr2 < N; ptr2++) {
		if (arr[ptr1] != arr[ptr2]) {
			ptr1++;
			arr[ptr1] = arr[ptr2];
		}
	}
	long long final_length = ptr1 + 1;
	for (long long i = 0; i < final_length; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}