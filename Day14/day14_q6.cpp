#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/rotting-oranges/

	Input:
	3 3
	2 1 1
	1 1 0
	0 1 1

	Output:
	4

	Input:
	3 3
	2 1 1
	0 1 1
	1 0 1

	Output:
	-1

	Input:
	1 2
	0 2

	Output:
	0
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	vector<vector<long long>> grid(N, vector<long long>(M));
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cin >> grid[i][j];
		}
	}

	// Method 1:
	// We will search for rottent oranges and turn the ones next to them to rotten evry iteration.
	// Time Complexity: O(n*m)
	// Space Complexity: O(n*m)
	queue<pair<long long, long long>> q;
	vector<long long> dir = { -1, 0, 1, 0, -1};
	long long fresh = 0;
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (grid[i][j] == 2) {
				q.push({i, j});
			}
			if (grid[i][j] == 1) {
				fresh++;
			}
		}
	}
	long long ans = -1;
	while (!q.empty()) {
		long long x = q.size();
		while (x--) {
			pair<long long, long long> p = q.front();
			q.pop();
			for (long long i = 0; i < 4; i++) {
				long long r = p.first + dir[i];
				long long c = p.second + dir[i + 1];
				if (r >= 0 && r < N && c >= 0 && c < M && grid[r][c] == 1) {
					grid[r][c] = 2;
					q.push({r, c});
					fresh--;
				}
			}
		}
		ans++;
	}
	if (fresh > 0) {
		cout << -1 << endl;
	}
	else if (ans == -1) {
		cout << 0 << endl;
	}
	else {
		cout << ans << endl;
	}
	return 0;
}