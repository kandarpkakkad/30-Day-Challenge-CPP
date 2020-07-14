#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/course-schedule
	https://leetcode.com/problems/course-schedule-ii

	You need to run the methods separately.

	Input:
	4 6
	0 1
	0 2
	1 2
	2 0
	2 3
	3 4

	Output:
	Yes
	Yes
	Yes
	Yes

	Input:
	4 4
	0 1
	1 2
	2 3
	3 4

	Output:
	No
	No
	No
	No
*/

void add_edge(vector<long long> adj[], long long u, long long v) {
	adj[u].push_back(v);
	// Comment the line below for directed graph.
	// adj[v].push_back(u);
}

bool has_cycle(vector<long long> adj[], long long u, long long V, vector<bool> &vis) {
	vector<long long> parent(V + 1, -1);
	queue<long long> q;
	vis[u] = true;
	q.push(u);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (long long i = 0; i < adj[u].size(); i++) {
			if (!vis[adj[u][i]]) {
				vis[adj[u][i]] = true;
				q.push(adj[u][i]);
				parent[adj[u][i]] = u;
			}
			else if (parent[u] != adj[u][i]) {
				return true;
			}
		}
	}
	return false;
}

bool has_cycle_2(vector<long long> adj[], long long u, bool vis[], long long parent) {
	vis[u] = true;
	for (long long i = 0; i < adj[u].size(); i++) {
		if (!vis[adj[u][i]]) {
			if (has_cycle_2(adj, adj[u][i], vis, u)) {
				return true;
			}
		}
		else if (adj[u][i] != parent) {
			return true;
		}
	}
	return false;
}

bool has_cycle_3(vector<long long> adj[], long long u, bool vis[], bool rec_stack[]) {
	if (!vis[u]) {
		vis[u] = true;
		rec_stack[u] = true;
		for (long long i = 0; i < adj[u].size(); i++) {
			if (!vis[adj[u][i]] && has_cycle_3(adj, adj[u][i], vis, rec_stack)) {
				return true;
			}
			else if (rec_stack[adj[u][i]]) {
				return true;
			}
		}
	}
	rec_stack[u] = false;
	return false;
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
	// We do a BFS traversal of the given graph. For every visited vertex ‘v’, if there is an adjacent ‘u’ such that u is already visited and u is not parent of v, then there is a cycle in graph. If we don’t find such an adjacent for any vertex, we say that there is no cycle. Undirected Graph.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	bool flag = false;
	vector<bool> vis(N + 1, false);
	for (long long i = 0; i < N + 1; i++) {
		if (!vis[i] && has_cycle(adj, i, N + 1, vis)) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// There is a cycle in a graph only if there is a back edge present in the graph. A back edge is an edge that is joining a node to itself (self-loop) or one of its ancestor in the tree produced by DFS. To find the back edge to any of its ancestor keep a visited array and if there is a back edge to any visited node then there is a loop and return true. Undirected Graph.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	bool vis[N + 1] = {false};
	bool flag = false;
	for (long long i = 0; i < N + 1; i++) {
		if (!vis[i]) {
			if (has_cycle_2(adj, i, vis, -1)) {
				flag = true;
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

	// Method 3:
	// There is a cycle in a graph only if there is a back edge present in the graph. A back edge is an edge that is from a node to itself (self-loop) or one of its ancestors in the tree produced by DFS. Directed Graph.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	bool vis[N + 1] = {false};
	bool rec_stack[N + 1] = {false};
	bool flag = false;
	for (long long i = 0; i < N + 1; i++) {
		if (has_cycle_3(adj, i, vis, rec_stack)) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 4:
	// We will use the similar method as above but use BFS. Directed Graph.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	vector<long long> in_degree(N + 1, 0);
	for (long long i = 0; i < N + 1; i++) {
		for (long long j = 0; j < adj[i][j]; j++) {
			in_degree[adj[u][i]]++;
		}
	}
	queue<long long> q;
	for (long long i = 0; i < N + 1; i++) {
		if (in_degree[i] == 0) {
			q.push(i);
		}
	}
	long long cnt = 0;
	vector<long long> top_order;
	while (!q.empty()) {
		long long u = q.front();
		q.pop();
		top_order.push_back(u);
		for (long long i = 0; i < adj[u].size(); i++) {
			if (--in_degree[adj[u][i]] == 0) {
				q.push(adj[u][i]);
			}
		}
		cnt++;
	}
	if (cnt != N + 1) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}