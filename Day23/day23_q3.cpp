#include<bits/stdc++.h>

using namespace std;

/*
	Prerequisite: https://www.geeksforgeeks.org/applications-of-breadth-first-traversal/

	https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

	Input:
	4 6
	0 1
	0 2
	1 2
	2 0
	2 3
	3 4

	Output:
	0 --> 1
	2
	1 --> 2
	2 --> 0
	3
	3 --> 4
	4 -->
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

	void bfs(long long u) {
		bool vis[V + 1] = {false};
		deque<long long> q;
		vis[u] = true;
		q.push_back(u);
		while (!q.empty()) {
			u = q.front();
			cout << u << " --> ";
			q.pop_front();
			for (long long i = 0; i < adj[u].size(); i++) {
				cout << adj[u][i] << endl;
				if (!vis[adj[u][i]]) {
					vis[adj[u][i]] = true;
					q.push_back(adj[u][i]);
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
	// We will use deque to use the front instead of back so that we can traverse the breath first.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	g.bfs(0);
	return 0;
}