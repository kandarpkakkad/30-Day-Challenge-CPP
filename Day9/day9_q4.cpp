#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/rat-in-a-maze-backtracking-2/

	Input:
	4 3
	1 0 0 0
	1 1 0 1
	0 1 0 0
	1 1 1 1

	Output:
	1 0 0 0
	1 1 0 0
	0 1 0 0
	0 1 1 1
*/

bool is_ok(vector<vector<bool>> maze, long long x, long long y) {
	if (x >= 0 && x < maze.size() && y >= 0 && y < maze.size() && maze[x][y] == 1) {
		return true;
	}
	return false;
}

bool solve(vector<vector<bool>> maze, long long x, long long y, vector<vector<bool>> &ans) {
	if (x == maze.size() - 1 && y == maze.size() - 1 && maze[x][y] == 1) {
		ans[x][y] = 1;
		return true;
	}
	if (is_ok(maze, x, y)) {
		ans[x][y] = 1;
		if (solve(maze, x + 1, y, ans)) {
			return true;
		}
		if (solve(maze, x, y + 1, ans)) {
			return true;
		}
		ans[x][y] = 0;
		return false;
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	vector<vector<bool>> maze;
	bool p;
	for (long long i = 0; i < N; i++) {
		vector<bool> r;
		for (long long j = 0; j < N; j++) {
			cin >> p;
			r.push_back(p);
		}
		maze.push_back(r);
	}

	// Method 1:
	// Recursive method to find the path.
	// Time Complexity: O(2^(n^2))
	// Space Complexity: O(n^2)
	vector<vector<bool>> ans(N, vector<bool>(N, 0));
	if (!solve(maze, 0, 0, ans)) {
		cout << "No Solution" << endl;
	}
	else {
		for (long long i = 0; i < N; i++) {
			for (long long j = 0; j < N; j++) {
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}