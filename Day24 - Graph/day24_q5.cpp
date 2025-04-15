#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

/*
	https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/
	https://leetcode.com/problems/cheapest-flights-within-k-stops

	Input:
	4 14 2
	0 1 2
	0 3 6
	1 0 2
	1 2 3
	1 3 8
	1 4 5
	2 1 3
	2 4 7
	3 0 6
	3 1 8
	3 4 9
	4 1 5
	4 2 7
	4 3 9

	Output:
	1 -- 0 -- 2
	2 -- 1 -- 3
	-1 -- 2 -- 0
	0 -- 3 -- 6
	1 -- 4 -- 5
	Total cost: 16
*/

void add_edge(vector<pair<long long, long long>> adj[], long long u, long long v, long long w) {
	adj[u].push_back({v, w});
}

void prims(vector<pair<long long, long long>> adj[], long long V, long long src) {
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
	vector<long long> key(V, INF);
	vector<long long> parent(V, -1);
	vector<bool> mst_set(V, false);
	pq.push({0, src});
	key[src] = 0;
	while (!pq.empty()) {
		long long temp = pq.top().second;
		pq.pop();
		mst_set[temp] = true;
		for (long long i = 0; i < adj[temp].size(); i++) {
			long long v = adj[temp][i].first;
			long long w = adj[temp][i].second;
			if (mst_set[v] == false && key[v] > w) {
				key[v] = w;
				pq.push({key[v], v});
				parent[v] = temp;
			}
		}
	}
	long long sum = 0;
	for (long long i = 0; i < V; i++) {
		cout << parent[i] << " -- " << i << " -- " << key[i] << endl;
		sum += key[i];
	}
	cout << "Total cost: " << sum << endl;
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
	// The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, the other set contains the vertices not yet included. At every step, it considers all the edges that connect the two sets, and picks the minimum weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing MST. A group of edges that connects two set of vertices in a graph is called cut in graph theory. So, at every step of Prim’s algorithm, we find a cut (of two sets, one contains the vertices already included in MST and other contains rest of the verices), pick the minimum weight edge from the cut and include this vertex to MST Set (the set that contains already included vertices).
	// Time Complexity: O(Elog(V))
	// Space Complexity: O(V)
	prims(adj, N + 1, src);
	return 0;
}