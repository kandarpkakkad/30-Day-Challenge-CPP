#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

/*
	https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance

	Input:
	4 4
	0 1 5
	0 3 10
	1 2 3
	2 3 1

	Output:
	Final Matrix
	000 005 008 009
	INF 000 003 004
	INF INF 000 001
	INF INF INF 000
*/

void add_edge(vector<vector<long long>> &adj, long long u, long long v, long long w) {
	adj[u][v] = w;
}

void floyd_warshall(vector<vector<long long>> adj) {
	long long V = adj.size();
	vector<vector<long long>> dist(V, vector<long long>(V));
	for (long long i = 0; i < V; i++) {
		for (long long j = 0; j < V; j++) {
			dist[i][j] = adj[i][j];
		}
	}
	for (long long k = 0; k < V; k++) {
		for (long long i = 0; i < V; i++) {
			for (long long j = 0; j < V; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	cout << "Final Matrix" << endl;
	for (long long i = 0; i < V; i++) {
		for (long long j = 0; j < V; j++) {
			if (dist[i][j] == INF) {
				cout << "INF ";
			}
			else {
				printf("%.3lld ", dist[i][j]);
			}
		}
		cout << endl;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, u, v, w, src;
	cin >> N >> M;
	vector<vector<long long>> adj(N, vector<long long>(N));
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < N; j++) {
			if (i != j) {
				adj[i][j] = INF;
			}
			else {
				adj[i][j] = 0;
			}
		}
	}
	for (long long i = 0; i < M; i++) {
		cin >> u >> v >> w;
		add_edge(adj, u, v, w);
	}

	// Method 1:
	// We initialize the solution matrix same as the input graph matrix as a first step. Then we update the solution matrix by considering all vertices as an intermediate vertex. The idea is to one by one pick all vertices and updates all shortest paths which include the picked vertex as an intermediate vertex in the shortest path.
	// Time Complexity: O(V^3)
	// Space Complextiy: O(V^2)
	floyd_warshall(adj);
	return 0;
}