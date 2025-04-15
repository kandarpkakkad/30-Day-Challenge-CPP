#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/cheapest-flights-within-k-stops

	Input:
	4 14
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
	0 -- 1 -- 2
	1 -- 2 -- 3
	1 -- 4 -- 5
	0 -- 3 -- 6
	Total cost: 16
*/

long long find(long long x, long long parent[]) {
	if (x != parent[x]) {
		parent[x] = find(parent[x], parent);
	}
	return parent[x];
}

void kruskals(vector<pair<long long, pair<long long, long long>>> &adj, vector<pair<long long, pair<long long, long long>>> &mst, long long parent[]) {
	long long E = adj.size();
	long long total = 0;
	sort(adj.begin(), adj.end());
	for (long long i = 0; i < E; i++) {
		long long pu = find(adj[i].second.first, parent);
		long long pv = find(adj[i].second.second, parent);
		if (pu != pv) {
			mst.push_back(adj[i]); // add to set
			total += adj[i].first; // total cost
			parent[pu] = parent[pv]; // union
		}
	}
	long long NE = mst.size();
	for (long long i = 0; i < NE; i++) {
		cout << mst[i].second.first << " -- " << mst[i].second.second << " -- " << mst[i].first << endl;
	}
	cout << "Total cost: " << total << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, u, v, w;
	cin >> N >> M;
	vector<pair<long long, pair<long long, long long>>> adj, mst;
	long long parent[N + 1];
	for (long long i = 0; i < M; i++) {
		cin >> u >> v >> w;
		adj.push_back({w, {u, v}});
	}
	for (long long i = 0; i <= N; i++) {
		parent[i] = i;
	}

	// Method 1:
	// Below are the steps for finding MST using Kruskal’s algorithm
	// 1. Sort all the edges in non-decreasing order of their weight.
	// 2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. Else, discard it.
	// 3. Repeat step#2 until there are (V-1) edges in the spanning tree.
	// Time Complexity: O(Elog(V))
	// Space Complexity: O(max(V, E))
	kruskals(adj, mst, parent);
	return 0;
}