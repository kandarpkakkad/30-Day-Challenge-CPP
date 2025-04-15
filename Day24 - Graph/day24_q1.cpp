#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/longest-consecutive-sequence

	You need to run the methods separately.

	Input:
	4 5
	1 0
	0 2
	2 1
	0 3
	3 4

	Output:
	0 1 2
	3
	4

	4
	3
	1 2 0
*/

class Graph {
	long long V;
	vector<long long> *adj;
public:
	Graph(long long V) {
		this->V = V;
		adj = new vector<long long>[V];
	}

	void dfs(long long u, bool vis[]) {
		vis[u] = true;
		cout << u << " ";
		for (long long i = 0; i < adj[u].size(); i++) {
			if (!vis[adj[u][i]]) {
				dfs(adj[u][i], vis);
			}
		}
	}

	Graph get_transpose() {
		Graph g(V);
		for (long long u = 0; u < V; u++) {
			for (long long i = 0; i < adj[u].size(); i++) {
				g.adj[adj[u][i]].push_back(u);
			}
		}
		return g;
	}

	void add_edge(long long u, long long v) {
		adj[u].push_back(v);
	}

	void fill_order(long long u, bool vis[], stack<long long> &st) {
		vis[u] = true;
		for (long long i = 0; i < adj[u].size(); i++) {
			if (!vis[adj[u][i]]) {
				fill_order(adj[u][i], vis, st);
			}
		}
		st.push(u);
	}

	void print_strongly_connected_components() {
		stack<long long> st;
		bool vis[V] = {false};
		for (long long i = 0; i < V; i++) {
			if (!vis[i]) {
				fill_order(i, vis, st);
			}
		}
		Graph gr = get_transpose();
		for (long long i = 0; i < V; i++) {
			vis[i] = false;
		}
		while (!st.empty()) {
			long long u = st.top();
			st.pop();
			if (!vis[u]) {
				gr.dfs(u, vis);
				cout << endl;
			}
		}
	}
};

class Graph_tarjan {
	long long V;
	vector<long long> *adj;
public:
	Graph_tarjan(long long V) {
		this->V = V;
		adj = new vector<long long>[V];
	}

	void add_edge(long long u, long long v) {
		adj[u].push_back(v);
	}
	void dfs(long long u, long long discover[], long long low[], stack<long long> *st, bool stack_member[]) {
		static long long t = 0; // t = time
		discover[u] = low[u] = ++t;
		st->push(u);
		stack_member[u] = true;
		for (long long i = 0; i < adj[u].size(); i++) {
			if (discover[adj[u][i]] == -1) {
				dfs(adj[u][i], discover, low, st, stack_member);
				low[u] = min(low[u], low[adj[u][i]]);
			}
			else if (stack_member[adj[u][i]]) {
				low[u] = min(low[u], discover[adj[u][i]]);
			}
		}
		if (low[u] == discover[u]) {
			long long temp = 0;
			while (st->top() != u) {
				temp = st->top();
				cout << temp << " ";
				stack_member[temp] = false;
				st->pop();
			}
			temp = st->top();
			cout << temp << endl;
			stack_member[temp] = false;
			st->pop();
		}
	}

	void print_strongly_connected_components() {
		long long discover[V];
		long long low[V];
		bool stack_member[V] = {false};
		stack<long long> *st = new stack<long long>();
		memset(discover, -1, sizeof(discover));
		memset(low, -1, sizeof(low));
		for (long long i = 0; i < V; i++) {
			if (discover[i] == -1) {
				dfs(i, discover, low, st, stack_member);
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

	// Method 1:
	// Kosaraju's algorithm: https://www.geeksforgeeks.org/strongly-connected-components/
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	Graph gr(N + 1);
	for (long long i = 0; i < M; i++) {
		cin >> u >> v;
		gr.add_edge(u, v);
	}
	gr.print_strongly_connected_components();
	cout << endl;

	// Method 2:
	// Tarjan's Algorithm: https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
	// Better than above.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	Graph_tarjan gr2(N + 1);
	for (long long i = 0; i < M; i++) {
		cin >> u >> v;
		gr2.add_edge(u, v);
	}
	gr2.print_strongly_connected_components();
	return 0;
}