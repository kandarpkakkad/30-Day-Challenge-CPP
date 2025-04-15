#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/sudoku-solver/

	Input:
	5 3 0 0 7 0 0 0 0
	6 0 0 1 9 5 0 0 0
	0 9 8 0 0 0 0 6 0
	8 0 0 0 6 0 0 0 3
	4 0 0 8 0 3 0 0 1
	7 0 0 0 2 0 0 0 6
	0 6 0 0 0 0 2 8 0
	0 0 0 4 1 9 0 0 5
	0 0 0 0 8 0 0 7 9

	Output:
	5 3 4 6 7 8 9 1 2
	6 7 2 1 9 5 3 4 8
	1 9 8 3 4 2 5 6 7
	8 5 9 7 6 1 4 2 3
	4 2 6 8 5 3 7 9 1
	7 1 3 9 2 4 8 5 6
	9 6 1 5 3 7 2 8 4
	2 8 7 4 1 9 6 3 5
	3 4 5 2 8 6 1 7 9
*/

bool is_ok(vector<vector<long long>> &board, long long i, long long j, long long val) {
	long long row = i - i % 3;
	long long column = j - j % 3;
	// Check all rows of that column.
	for (long long x = 0; x < 9; x++) {
		if (board[x][j] == val) {
			return false;
		}
	}
	// Check all columns of that row.
	for (long long y = 0; y < 9; y++) {
		if (board[i][y] == val) {
			return false;
		}
	}
	// 3x3 matricx checking.
	for (long long x = 0; x < 3; x++) {
		for (long long y = 0; y < 3; y++) {
			if (board[row + x][column + y] == val) {
				return false;
			}
		}
	}
	return true;
}

bool solve(vector<vector<long long>> &board, long long i, long long j) {
	if (i == 9) {
		return true;
	}
	if (j == 9) {
		return solve(board, i + 1, 0);
	}
	if (board[i][j] != 0) {
		return solve(board, i, j + 1);
	}
	for (long long c = 1; c <= 9; c++) {
		if (is_ok(board, i, j, c)) {
			board[i][j] = c;
			if (solve(board, i, j + 1)) {
				return true;
			}
			board[i][j] = 0;
		}
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N = 9;
	vector<vector<long long>> board;
	long long q;
	for (long long i = 0; i < N; i++) {
		vector<long long> r;
		for (long long j = 0; j < N; j++) {
			cin >> q;
			r.push_back(q);
		}
		board.push_back(r);
	}

	// Method 1:
	// Recursive method to check all the possibilities.
	// Time Complexity: O(9*(n^2)) = O(n^2)
	// Space Complexity: O(n^2)
	if (solve(board, 0, 0)) {
		for (long long i = 0; i < N; i++) {
			for (long long j = 0; j < N; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else {
		cout << "No Solution" << endl;
	}
	return 0;
}