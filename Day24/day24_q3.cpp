#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

/*
	https://leetcode.com/problems/cheapest-flights-within-k-stops

	Input:
	5 8 0
	0 1 -1
	0 2 4
	1 2 3
	1 3 2
	1 4 2
	3 2 5
	3 1 1
	4 3 -3

	Output:
	Vertex distance from the source
	0 -- 0
	1 -- -1
	2 -- 2
	3 -- -2
	4 -- 1
	5 -- 1061109567
*/

void add_edge(vector<pair<long long, long long>> adj[], long long u, long long v, long long w) {
	adj[u].push_back({v, w});
}

void bellman_ford(vector<pair<long long, long long>> adj[], long long V, long long src) {
	vector<long long> dist(V, INF);
	dist[src] = 0;
	for (long long k = 0; k < V; k++) {
		for (long long i = 0; i < V; i++) {
			for (long long j = 0; j < adj[i].size(); j++) {
				long long u = i;
				long long v = adj[i][j].first;
				long long w = adj[i][j].second;
				if (dist[u] != INF && dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
				}
			}
		}
	}
	for (long long i = 0; i < V; i++) {
		for (long long j = 0; j < adj[i].size(); j++) {
			long long u = i;
			long long v = adj[i][j].first;
			long long w = adj[i][j].second;
			if (dist[u] != INF && dist[v] > dist[u] + w) {
				cout << "Negative edge cycle detected." << endl;
				return;
			}
		}
	}
	cout << "Vertex distance from the source" << endl;
	for (long long i = 0; i < V; i++) {
		cout << i << " -- " << dist[i] << endl;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, u, v, w, src;
	cin >> N >> M >> src;
	vector<pair<long long, long long>> adj[N + 1];
	for (long long i = 0; i < M; i++) {
		cin >> u >> v >> w;
		add_edge(adj, u, v, w);
	}

	// Method 1:
	// Dijkstra doesn’t work for Graphs with negative weight edges, Bellman-Ford works for such graphs. Bellman-Ford is also simpler than Dijkstra and suites well for distributed systems.
	// Time Complexity: O(VE)
	// Space Complexity: O(V)
	bellman_ford(adj, N + 1, src);
	return 0;
}