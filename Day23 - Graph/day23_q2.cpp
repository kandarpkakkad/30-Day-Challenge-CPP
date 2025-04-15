#include<bits/stdc++.h>

using namespace std;

/*
	Prerequisite: https://www.geeksforgeeks.org/applications-of-depth-first-search/

	https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/

	Input:
	4 6
	0 1
	0 2
	1 2
	2 0
	2 3
	3 4

	Output:
	0 -- > 1
	1 -- > 2
	2 -- > 0
	3
	3 -- > 4
	4 -- > 2

	0 --> 1
	2
	2 --> 0
	3
	3 --> 4
	4 --> 1 --> 2
*/

class Graph {
	long long V;
	vector<long long> *adj;
public:
	Graph(long long V) {
		this->V = V;
		adj = new vector<long long>[V + 1];
	}

	void add_edge(long long u, long long v) {
		adj[u].push_back(v);
	}

	void dfs_util(long long u, bool vis[]) {
		vis[u] = true;
		cout << u << " -- > ";
		for (long long i = 0; i < adj[u].size(); i++) {
			cout << adj[u][i] << endl;
			if (!vis[adj[u][i]]) {
				dfs_util(adj[u][i], vis);
			}
		}
	}

	void dfs() {
		bool vis[V + 1] = {false};
		for (long long i = 0; i < V; i++) {
			if (vis[i] == false) {
				dfs_util(i, vis);
			}
		}
	}

	void dfs_2(long long u) {
		vector<bool> vis(V, false);
		stack<long long> st;
		st.push(u);
		while (!st.empty()) {
			u = st.top();
			st.pop();
			if (!vis[u]) {
				cout << u << " --> ";
				vis[u] = true;
			}
			for (long long i = 0; i < adj[u].size(); i++) {
				cout << adj[u][i] << endl;
				if (!vis[adj[u][i]]) {
					st.push(adj[u][i]);
				}
			}
		}

	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, u, v;
	cin >> N >> M;
	Graph g(N);
	for (long long i = 0; i < M; i++) {
		cin >> u >> v;
		g.add_edge(u, v);
	}

	// Method 1:
	// We use recursive method to traverse the children first.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V) (recursive stack)
	g.dfs();
	cout << endl;

	// Method 2:
	// We will do the same thing but with iteration for which we will use stack to store the children.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	g.dfs_2(0);
	return 0;
}