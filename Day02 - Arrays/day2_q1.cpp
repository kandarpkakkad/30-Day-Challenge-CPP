#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/set-matrix-zeroes/

	You need to run the methods one by one.

	Input:
	3 4
	0 1 2 0
	3 4 5 2
	1 3 1 5

	Output:
	0 0 0 0
	0 4 5 2
	0 3 1 5

	0 0 0 0
	0 4 5 2
	0 3 1 5

	0 0 0 0
	0 4 5 2
	0 3 1 5
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long arr[N][M];
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	// Method 1:
	// Naive Method. We traverse through matrix and if we find any 0 we change the row and column of that 0 to 0.
	// Time Complexity: O(n*m*(n+m))
	// Space Complexity: O(1)
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (arr[i][j] == 0) {
				for (long long k = 0; k < N; k++) {
					arr[k][j] = -1;
				}
				for (long long k = 0; k < M; k++) {
					arr[i][k] = -1;
				}
			}
		}
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (arr[i][j] == -1) {
				arr[i][j] = 0;
			}
		}
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Method 2:
	// We will create two sets that will store the rows and columns which has 0 and then we will make those rows and columns 0
	// Time Complexity = O(n*m)
	// Space Complexity = O(n + m)
	set<long long> row, col;
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (arr[i][j] == 0) {
				row.insert(i);
				col.insert(j);
			}
		}
	}
	for (auto it = row.begin(); it != row.end(); it++) {
		for (long long i = 0; i < M; i++) {
			arr[*it][i] = 0;
		}
	}
	for (auto it = col.begin(); it != col.end(); it++) {
		for (long long i = 0; i < N; i++) {
			arr[i][*it] = 0;
		}
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Method 3:
	// Here we will make the 0s on the 0th row and col on the basis of 0 in the ith row or col. Then we will convert every row and col to 0 that has 0 in the 0th row and col respectively.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	bool is_row_zero = false;
	bool is_col_zero = false;
	for (long long i = 0; i < N; i++) {
		if (arr[i][0] == 0) {
			is_col_zero = true;
			break;
		}
	}
	for (long long i = 0; i < M; i++) {
		if (arr[0][i] == 0) {
			is_row_zero = true;
			break;
		}
	}
	for (long long i = 1; i < N; i++) {
		for (long long j = 1; j < M; j++) {
			if (arr[i][j] == 0) {
				arr[i][0] = 0;
				arr[0][j] = 0;
			}
		}
	}
	for (long long i = 1; i < N; i++) {
		for (long long j = 1; j < M; j++) {
			if (arr[i][0] == 0 || arr[0][j] == 0) {
				arr[i][j] = 0;
			}
		}
	}
	if (is_row_zero) {
		for (long long i = 0; i < M; i++) {
			arr[0][i] = 0;
		}
	}
	if (is_col_zero) {
		for (long long i = 0; i < N; i++) {
			arr[i][0] = 0;
		}
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}