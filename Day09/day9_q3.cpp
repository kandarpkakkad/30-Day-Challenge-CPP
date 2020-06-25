#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/m-coloring-problem-backtracking-5/

	Input:
	4 3
	0 1 1 1
	1 0 1 0
	1 1 0 1
	1 0 1 0

	Output:
	1 2 3 2

	Input:
	4 3
	1 1 1 1
	1 1 1 1
	1 1 1 1
	1 1 1 1

	Output:
	No Solution
*/

bool is_ok(long long &u, vector<vector<bool>> graph, vector<long long> &color, long long &c) {
	for (long long i = 0; i < graph.size(); i++) {
		if (graph[u][i] && c == color[i]) {
			return false;
		}
	}
	return true;
}

bool solve(vector<vector<bool>> graph, long long m, vector<long long> &color, long long u) {
	if (u == graph.size()) {
		return true;
	}
	for (long long c = 1; c <= m; c++) {
		if (is_ok(u, graph, color, c)) {
			color[u] = c;
			if (solve(graph, m, color, u + 1)) {
				return true;
			}
			color[u] = 0;
		}
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	vector<vector<bool>> graph;
	bool p;
	for (long long i = 0; i < N; i++) {
		vector<bool> r;
		for (long long j = 0; j < N; j++) {
			cin >> p;
			r.push_back(p);
		}
		graph.push_back(r);
	}

	// Method 1:
	// Recursive method to see if every vertices is coloured such that no two adjacent vertices are of same colour.
	// Time Complexity: O(n*m)
	// Space Complexity: O(n)
	vector<long long> color(N, 0);
	if (!solve(graph, M, color, 0)) {
		cout << "No Solution" << endl;
	}
	else {
		for (long long i = 0; i < N; i++) {
			cout << color[i] << " ";
		}
		cout << endl;
	}
	return 0;
}