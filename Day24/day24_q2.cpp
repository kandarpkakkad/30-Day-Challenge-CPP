#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

/*
	https://leetcode.com/problems/network-delay-time

	Input:
	9 14 5
	0 1 4
	0 7 8
	1 2 8
	1 7 11
	2 3 7
	2 8 2
	2 5 4
	3 4 9
	3 5 14
	4 5 10
	5 6 2
	6 7 1
	6 8 6
	7 8 7

	Output:
	Vertex distance fron source
	0 -- 11
	1 -- 12
	2 -- 4
	3 -- 11
	4 -- 10
	5 -- 0
	6 -- 2
	7 -- 3
	8 -- 6
	Vertex distance fron source
	0 -- 11
	1 -- 12
	2 -- 4
	3 -- 11
	4 -- 10
	5 -- 0
	6 -- 2
	7 -- 3
	8 -- 6
*/

void add_edge(vector<pair<long long, long long>> adj[], long long u, long long v, long long w) {
	adj[u].push_back({v, w});
	adj[v].push_back({u, w});
}

void dijkstras_1(vector<pair<long long, long long>> adj[], long long V, long long src) {
	set<pair<long long, long long>> processing;
	vector<long long> dist(V, INF); // vector with distances = Infinite
	processing.insert({0, src});
	dist[src] = 0;
	while (!processing.empty()) {
		pair<long long, long long> temp = *(processing.begin());
		processing.erase(processing.begin());
		long long u = temp.second;
		for (long long i = 0; i < adj[u].size(); i++) {
			long long v = adj[u][i].first;
			long long w = adj[u][i].second;
			if (dist[v] > dist[u] + w) {
				if (dist[v] != INF) {
					processing.erase(processing.find({dist[v], v}));
				}
				dist[v] = dist[u] + w;
				processing.insert({dist[v], v});
			}
		}
	}
	cout << "Vertex distance fron source" << endl;
	for (long long i = 0; i < V - 1; i++) {
		cout << i << " -- " << dist[i] << endl;
	}
}

void dijkstras_2(vector<pair<long long, long long>> adj[], long long V, long long src) {
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
	vector<long long> dist(V, INF);
	pq.push({0, src});
	dist[src] = 0;
	while (!pq.empty()) {
		long long u = pq.top().second;
		pq.pop();
		for (long long i = 0; i < adj[u].size(); i++) {
			long long v = adj[u][i].first;
			long long w = adj[u][i].second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
	cout << "Vertex distance fron source" << endl;
	for (long long i = 0; i < V - 1; i++) {
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
	// Set keeps all its keys in sorted order so minimum distant vertex will always be at beginning. And if the vertex is processed then we dont reach it again. And we keep on seeing the vertices that is not processed and has minimum distance from initial source.
	// Time Complexity: O(Elog(V))
	// Space Complexity: O(V)
	dijkstras_1(adj, N + 1, src);

	// Method 2:
	// For Dijkstra’s algorithm, it is always recommended to use heap (or priority queue) as the required operations (extract minimum and decrease key) match with speciality of heap (or priority queue). However, the problem is, priority_queue doesn’t support decrease key. To resolve this problem, do not update a key, but insert one more copy of it.
	// Time Complexity: O(Elog(V))
	// Space Complexity: O(V)
	dijkstras_2(adj, N + 1, src);
	return 0;
}