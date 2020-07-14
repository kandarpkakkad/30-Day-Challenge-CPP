#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/is-graph-bipartite/

	Input:
	4 8
	0 1
	0 3
	1 0
	1 2
	2 1
	2 3
	3 0
	3 2

	Output:
	Yes
	Yes

	Input:
	5 5
	1 2
	2 3
	3 4
	4 5
	5 1

	Output:
	No
	No
*/

void add_edge(vector<long long> adj[], long long u, long long v) {
	adj[u].push_back(v);
}

bool is_bipartite(vector<long long> adj[], long long src, long long V, long long color[]) {
	color[src] = 1;
	queue<long long> q;
	q.push(src);
	while (!q.empty()) {
		long long u = q.front();
		q.pop();
		for (long long i = 0; i < adj[u].size(); i++) {
			if (adj[u][i] == u) {
				return false;
			}
			if (color[adj[u][i]] == -1) {
				color[adj[u][i]] = 1 - color[u];
				q.push(adj[u][i]);
			}
			else if (color[adj[u][i]] == color[u]) {
				return false;
			}
		}
	}
	return true;
}

bool is_bipartite_2(vector<long long> adj[], long long color[], long long pos, long long next_color, long long V) {
	if (color[pos] != -1 && color[pos] != next_color) {
		return false;
	}
	color[pos] = next_color;
	bool ans = true;
	for (long long i = 0; i < adj[pos].size(); i++) {
		if (color[adj[pos][i]] == -1) {
			ans = ans & is_bipartite_2(adj, color, adj[pos][i], 1 - next_color, V);
		}
		if (color[adj[pos][i]] != -1 && color[adj[pos][i]] != 1 - next_color) {
			return false;
		}
		if (!ans) {
			return false;
		}
	}
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, u, v;
	cin >> N >> M;
	vector<long long> adj[N + 1];
	for (long long i = 0; i < M; i++) {
		cin >> u >> v;
		add_edge(adj, u, v);
	}

	// Method 1:
	// We use simple method. We color each vertex of a node of one color with second color and if parent and child are colored with same color then it cannot be bipartite. If we dont use for loop we can only check connected graphs. But here we can check disconnected graphs as well.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	long long color[N + 1];
	for (long long i = 0; i < N + 1; i++) {
		color[i] = -1;
	}
	bool flag = true;
	for (long long i = 0; i < N + 1; i++) {
		if (color[i] == -1) {
			if (!is_bipartite(adj, i, N + 1, color)) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// This is rather a simple method. We use DFS traversal and assign the alternate colors to child, parent and so on.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	// long long color[N + 1];
	for (long long i = 0; i < N + 1; i++) {
		color[i] = -1;
	}
	long long pos = 0;
	flag = true;
	for (long long i = 0; i < N + 1; i++) {
		if (color[i] == -1) {
			if (!is_bipartite_2(adj, color, pos, i, N + 1)) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}