#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/bfs-using-stl-competitive-coding/

	Input:
	8 10
	0 1
	0 2
	0 3
	0 4
	1 5
	2 5
	3 6
	4 6
	5 7
	6 7

	Output:
	0 1 2 3 4 5 6 7
*/

void bfs_it(vector<vector<long long>> &g, vector<long long> &v, long long u) {
	queue<long long> q;
	q.push(u);
	v[u] = true;
	while (!q.empty()) {
		long long f = q.front();
		q.pop();
		cout << f << " ";
		for (long long i = 0; i < g[f].size(); i++) {
			if (v[g[f][i]] == false) {
				q.push(g[f][i]);
				v[g[f][i]] = true;
			}
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long V, E;
	cin >> V >> E;
	vector<long long> vertex;
	vector<vector<long long>> graph;
	vertex.assign(V, false);
	graph.assign(V, vector<long long>());
	long long a, b;
	for (long long i = 0; i < E; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
	}

	for (long long i = 0; i < V; i++) {
		if (vertex[i] == false) {
			bfs_it(graph, vertex, i);
		}
	}
	cout << endl;
	return 0;
}