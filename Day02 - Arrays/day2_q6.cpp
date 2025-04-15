#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/rotate-image/

	Input:
	3
	1 2 3
	4 5 6
	7 8 9

	Output:
	7 4 1
	8 5 2
	9 6 3
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long arr[N][N];
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	// Method 1:
	// Store the current element of matrix in a variable and shift the rest across that index's row and column.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	for (long long i = 0; i < N / 2; i++) {
		for (long long j = i; j < N - i - 1; j++) {
			long long temp = arr[i][j];
			arr[i][j] = arr[N - j - 1][i];
			arr[N - j - 1][i] = arr[N - i - 1][N - j - 1];
			arr[N - i - 1][N - j - 1] = arr[j][N - i - 1];
			arr[j][N - i - 1] = temp;
			// for (long long k = 0; k < N; k++) {
			// 	for (long long l = 0; l < N; l++) {
			// 		cout << arr[k][l] << " ";
			// 	}
			// 	cout << endl;
			// }
			// cout << endl;
		}
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}