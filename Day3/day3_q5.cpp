#include<bits/stdc++.h>

using namespace std;

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
	// M is cols and N is rows. Create a grid of N rows and M cols prefilled with 1 because initially we assume that there is only one way to reach all the cells in reality, there is only one way to reach the first column and first row of the grid. So start from 1 to N and 1 to M.
	// Time Complexity: O(n*m)
	// Space Complexity: O(n*m)
	vector<vector<long long>> g;
	for (long long i = 0; i < N; i++) {
		vector<long long> temp;
		for (long long j = 0; j < M; j++) {
			temp.push_back(1);
		}
		g.push_back(temp);
	}

	for (long long i = 1; i < N; i++) {
		for (long long j = 1; j < M; j++) {
			g[i][j] = g[i - 1][j] + g[i][j - 1];
		}
	}
	cout << g[N - 1][M - 1] << endl;
	return 0;
}