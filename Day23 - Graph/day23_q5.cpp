#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/tag/topological-sort/
	https://www.geeksforgeeks.org/topological-sorting/

	You need to run the methods separately.

	Input:
	5 6
	2 3
	3 1
	4 0
	4 1
	5 0
	5 2

	Output:
	5 4 2 3 1 0

	4 5 0 2 3 1
	4 5 2 0 3 1
	4 5 2 3 0 1
	4 5 2 3 1 0
	5 2 3 4 0 1
	5 2 3 4 1 0
	5 2 4 0 3 1
	5 2 4 3 0 1
	5 2 4 3 1 0
	5 4 0 2 3 1
	5 4 2 0 3 1
	5 4 2 3 0 1
	5 4 2 3 1 0

	4 5 0 2 3 1
*/

void add_edge(vector<long long> adj[], long long u, long long v, vector<long long> &in_degree) {
	adj[u].push_back(v);
	in_degree[v]++;
}

void topological_sort(vector<long long> adj[], long long u, bool vis[], stack<long long> &st) {
	vis[u] = true;
	for (long long i = 0; i < adj[u].size(); i++) {
		if (!vis[adj[u][i]]) {
			topological_sort(adj, adj[u][i], vis, st);
		}
	}
	st.push(u);
}

void all_topological_sort(vector<long long> adj[], vector<long long> &ans, bool vis[], long long V, vector<long long> &in_degree) {
	bool flag = false;
	for (long long i = 0; i < V; i++) {
		if (in_degree[i] == 0 && !vis[i]) {
			for (long long j = 0; j < adj[i].size(); j++) {
				in_degree[adj[i][j]]--;
			}
			ans.push_back(i);
			vis[i] = true;
			all_topological_sort(adj, ans, vis, V, in_degree);
			vis[i] = false;
			ans.erase(ans.end() - 1);
			for (long long j = 0; j < adj[i].size(); j++) {
				in_degree[adj[i][j]]++;
			}
			flag = true;
		}
	}
	if (!flag) {
		for (long long i = 0; i < ans.size(); i++) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, u, v;
	cin >> N >> M;
	vector<long long> adj[N + 1];
	vector<long long> in_degree(N + 1, 0);
	for (long long i = 0; i < M; i++) {
		cin >> u >> v;
		add_edge(adj, u, v, in_degree);
	}

	// Method 1:
	// Recursive method similar to DFS but with modifications.  In topological sorting, we use a temporary stack. We don’t print the vertex immediately, we first recursively call topological sorting for all its adjacent vertices, then push it to a stack. Her we are printing only one of the possible topological sort.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	stack<long long> st;
	bool vis[N + 1] = {false};
	for (long long i = 0; i < N + 1; i++) {
		if (!vis[i]) {
			topological_sort(adj, i, vis, st);
		}
	}
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}

	// Method 2:
	// Here we will print all the possible topological sorts of a graph using backtracking and performing the method above.
	// Time Complexity: O(V^2)
	// Space Complexity: O(V^2)
	bool vis[N + 1] = {false};
	vector<long long> ans;
	all_topological_sort(adj, ans, vis, N + 1, in_degree);

	// Method 3:
	// What we will be doing is pick all the vertices with in_degree 0 and add it to queue. Remove a vertex from the queue and then decrease the in_degree by 1 for all neighbours and if it becomes 0, add it to queue and also increment the count by 1 till the queue is empty. If count is not equal to number of vertices then there is a cycle else print the topological sort.
	// Benefit of this method is that it is not necessary to give input as acyclic graph. It will detect cycle if it exists.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	queue<long long> q;
	for (long long i = 0; i < N + 1; i++) {
		if (in_degree[i] == 0) {
			q.push(i);
		}
	}
	long long cnt = 0;
	vector<long long> top_order;
	while (!q.empty()) {
		long long w = q.front();
		q.pop();
		top_order.push_back(w);
		for (long long i = 0; i < adj[w].size(); i++) {
			if (--in_degree[adj[w][i]] == 0) {
				q.push(adj[w][i]);
			}
		}
		cnt++;
	}
	if (cnt != N + 1) {
		cout << "There is a cycle." << endl;
	}
	else {
		for (long long i = 0; i < top_order.size(); i++) {
			cout << top_order[i] << " ";
		}
		cout << endl;
	}
	return 0;
}