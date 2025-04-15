#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/n-queens/

	Input:
	4

	Output:
	Solution 1
	_ _ Q _
	Q _ _ _
	_ _ _ Q
	_ Q _ _

	Solution 2
	_ Q _ _
	_ _ _ Q
	Q _ _ _
	_ _ Q _
*/

bool is_ok(vector<string> &board, long long row, long long col, long long N) {
	for (long long i = 0; i < col; i++) {
		if (board[row][i] == 'Q') {
			return false;
		}
	}
	for (long long i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 'Q') {
			return false;
		}
	}
	for (long long i = row, j = col; i < N && j >= 0; i++, j--) {
		if (board[i][j] == 'Q') {
			return false;
		}
	}
	return true;
}

void solve_n_queens(vector<vector<string>> &ans, vector<string> &board, long long col, long long N) {
	if (col >= N) {
		ans.push_back(board);
		return;
	}
	for (long long i = 0; i < N; i++) {
		if (is_ok(board, i, col, N)) {
			board[i][col] = 'Q';
			solve_n_queens(ans, board, col + 1, N);
			board[i][col] = '_';
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;

	// Method 1:
	// We will use recursive methods in backtracking as it is easy to understand and short to write. We place Qs and dont keep other Qs in that diagonal or row or column.
	// Time Complexity: O(2^n)
	// Space Complexity: O(n^2)
	vector<vector<string>> ans;
	vector<string> board(N, string(N, '_'));
	solve_n_queens(ans, board, 0, N);
	for (long long j = 0; j < ans.size(); j++) {
		cout << "Solution " << j  + 1 << endl;
		for (long long i = 0; i < ans[j].size(); i++) {
			for (long long k = 0; k < ans[j][i].size(); k++) {
				cout << ans[j][i][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}