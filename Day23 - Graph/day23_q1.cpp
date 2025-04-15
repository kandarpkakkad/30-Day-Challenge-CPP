#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/clone-graph/

	Input:
	4 4
	1 2
	1 4
	2 3
	3 4

	Output:
	Original
	Val: 1
	Edges: 2 4
	Val: 2
	Edges: 1 3
	Val: 4
	Edges: 1 3
	Val: 3
	Edges: 2 4

	Copy
	Val: 1
	Edges: 2 4
	Val: 2
	Edges: 1 3
	Val: 4
	Edges: 1 3
	Val: 3
	Edges: 2 4
*/

struct graph_node {
	long long key;
	vector<struct graph_node *> edges;
	graph_node(long long val) {
		key = val;
		edges = {};
	}
} *NEW, *head;

struct graph_node *clone_graph(struct graph_node *head) {
	unordered_map<struct graph_node*, struct graph_node*> um;
	queue<struct graph_node*> q;
	q.push(head);
	struct graph_node *node;
	node = new graph_node(head->key);
	um[head] = node;
	while (!q.empty()) {
		struct graph_node *u = q.front();
		q.pop();
		vector<struct graph_node *> v = u->edges;
		long long n = v.size();
		for (long long i = 0; i < n; i++) {
			if (um[v[i]] == NULL) {
				node = new graph_node(v[i]->key);
				um[v[i]] = node;
				q.push(v[i]);
			}
			um[u]->edges.push_back(um[v[i]]);
		}
	}
	return um[head];
}

void bfs(struct graph_node *head) {
	map<struct graph_node*, bool> vis;
	queue<struct graph_node *> q;
	q.push(head);
	vis[head] = true;
	while (!q.empty()) {
		struct graph_node *u = q.front();
		q.pop();
		cout << "Val: " << u->key << endl;
		cout << "Edges: ";
		for (long long i = 0; i < u->edges.size(); i++) {
			cout << u->edges[i]->key << " ";
			if (!vis[u->edges[i]]) {
				vis[u->edges[i]] = true;
				q.push(u->edges[i]);
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
	long long N, M, u, v;
	cin >> N >> M;
	unordered_map<long long, struct graph_node*> um;
	long long mn = LLONG_MAX;
	for (long long i = 0; i < M; i++) {
		cin >> u >> v;
		if (um.find(u) != um.end() && um.find(v) != um.end()) {
			um[u]->edges.push_back(um[v]);
			um[v]->edges.push_back(um[u]);
		}
		if (um.find(u) != um.end() && um.find(v) == um.end()) {
			NEW = new graph_node(v);
			um[v] = NEW;
			um[v]->edges.push_back(um[u]);
			um[u]->edges.push_back(um[v]);
		}
		if (um.find(u) == um.end() && um.find(v) != um.end()) {
			NEW = new graph_node(u);
			um[u] = NEW;
			um[u]->edges.push_back(um[v]);
			um[v]->edges.push_back(um[u]);
		}
		if (um.find(u) == um.end() && um.find(v) == um.end()) {
			NEW = new graph_node(u);
			um[u] = NEW;
			NEW = new graph_node(v);
			um[v] = NEW;
			um[v]->edges.push_back(um[u]);
			um[u]->edges.push_back(um[v]);
		}
		mn = min(mn, min(u, v));
	}
	head = um[mn];
	cout << "Original" << endl;
	bfs(head);
	cout << endl;
	cout << "Copy" << endl;

	// Method 1:
	// We do BFS traversal and add the node of the graph respectively in the copy.
	// Time Complexity: O(V+E)
	// Space Complexity: O(V)
	struct graph_node *copy = clone_graph(head);
	bfs(copy);
	return 0;
}