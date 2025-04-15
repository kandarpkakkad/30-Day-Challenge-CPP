#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/number-of-islands/

	You need to run the methods separately.

	Input:
	4 5
	1 1 1 1 0
	1 1 0 1 0
	1 1 0 0 0
	0 0 0 0 0

	Output:
	1
	1

	Input:
	4 5
	1 1 0 0 0
	1 1 0 0 0
	0 0 1 0 0
	0 0 0 1 1

	Output:
	3
	3
*/

class DSU {
	vector<long long> rank;
	vector<long long> parent;
	long long N;
public:
	DSU(long long N) {
		this->N = N;
		rank.resize(N);
		parent.resize(N);
		for (long long i = 0; i < N; i++) {
			parent[i] = i;
		}
	}

	long long find(long long x) {
		if (parent[x] != x) {
			// Decrease the height of the tree.
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void Union(long long x, long long y) {
		long long x_rep = find(x);
		long long y_rep = find(y);
		if (x_rep == y_rep) {
			return;
		}
		if (rank[x_rep] < rank[y_rep]) {
			parent[x_rep] = y_rep;
		}
		else if (rank[y_rep] < rank[x_rep]) {
			parent[y_rep] = x_rep;
		}
		else {
			parent[y_rep] = x_rep;
			rank[x_rep]++;
		}
	}
};

long long count_islands(vector<vector<long long>> &grid) {
	long long N = grid.size();
	long long M = grid[0].size();
	DSU *dsu = new DSU(N * M);
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (grid[i][j] == 0) {
				continue;
			}
			if (i + 1 < N && grid[i + 1][j] == 1) {
				dsu->Union(i * M + j, (i + 1) * M + j);
			}
			if (i - 1 >= 0 && grid[i - 1][j] == 1) {
				dsu->Union(i * M + j, (i - 1) * M + j);
			}
			if (j + 1 < M && grid[i][j + 1] == 1) {
				dsu->Union(i * M + j, i * M + (j + 1));
			}
			if (j - 1 >= 0 && grid[i][j - 1] == 1) {
				dsu->Union(i * M + j, i * M + (j - 1));
			}
			// Uncomment the code below if you want to check diagonally as well.
			// if (i + 1 < N && j + 1 < M && grid[i + 1][j + 1] == 1) {
			// 	dsu->Union(i * M + j, (i + 1) * M + (j + 1));
			// }
			// if (i + 1 < N && j - 1 >= 0 && grid[i + 1][j - 1] == 1) {
			// 	dsu->Union(i * M + j, (i + 1) * M + (j - 1));
			// }
			// if (i - 1 >= 0 && j + 1 < M && grid[i - 1][j + 1] == 1) {
			// 	dsu->Union(i * M + j, (i - 1) * M + (j + 1));
			// }
			// if (i - 1 >= 0 && j - 1 >= 0 && grid[i - 1][j - 1] == 1) {
			// 	dsu->Union(i * M + j, (i - 1) * M + (j - 1));
			// }
		}
	}
	long long freq[N * M] = {0};
	long long ans = 0;
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {

			if (grid[i][j] == 1) {
				long long x = dsu->find(i * M + j);
				if (freq[x] == 0) {
					ans++;
					freq[x]++;
				}
				else {
					freq[x]++;
				}
			}
		}
	}
	return ans;
}

void dfs(vector<vector<long long>> &grid, long long i, long long j) {
	long long N = grid.size();
	long long M = grid[0].size();
	if (i < 0 || i == N || j < 0 || j == M || grid[i][j] == 0) {
		return;
	}
	grid[i][j] = 0;
	dfs(grid, i - 1, j);
	dfs(grid, i + 1, j);
	dfs(grid, i, j - 1);
	dfs(grid, i, j + 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, x;
	cin >> N >> M;
	vector<vector<long long>> arr;
	for (long long i = 0; i < N; i++) {
		vector<long long> r;
		for (long long j = 0; j < M; j++) {
			cin >> x;
			r.push_back(x);
		}
		arr.push_back(r);
	}

	// Method 1:
	// The idea is simple. We need to find disconnected graphs. We will do it using DFS.
	// Time Complexity: O(n*m)
	// Space Complexity: O(n*m) (recursive stack)
	long long ans = 0;
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			if (arr[i][j] == 1) {
				ans++;
				dfs(arr, i, j);
			}
		}
	}
	cout << ans << endl;

	// Method 2:
	// We will use DSU to merge the islands and the remaining sets at the end will the count of islands.
	cout << count_islands(arr) << endl;
	return 0;
}
