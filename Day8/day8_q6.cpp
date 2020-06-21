#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/maximum-length-of-pair-chain

	Input:
	5
	1 2 100
	2 1 19
	3 2 27
	4 1 25
	5 3 15

	Output:
	3 1 5
	1 3 5
*/

struct DisjointSet {
	long long *parent;

	DisjointSet(long long n) {
		parent = new long long[n + 1];
		for (long long i = 0; i < n + 1; i++) {
			parent[i] = i;
		}
	}

	long long find(long long f) {
		// Make the parent of the nodes in the path from u--> parent[u] point to parent[u]
		if (f == parent[f]) {
			return f;
		}
		return parent[f] = find(parent[f]);
	}

	void merge(long long u, long long v) {
		// Update the greatest available free slot to u
		parent[v] = u;
	}
};

long long find_max(vector<vector<long long>> arr, long long N) {
	long long ans = LLONG_MIN;
	for (long long i = 0; i < N; i++) {
		ans = max(ans, arr[i][1]);
	}
	return ans;
}

bool comparator(vector<long long> a, vector<long long> b) {
	return a[2] > b[2];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long id, end, profit;
	vector<vector<long long>> arr(N, vector<long long>(3));
	for (long long i = 0; i < N; i++) {
		cin >> id >> end >> profit;
		arr.push_back({id, end, profit});
	}

	// Method 1:
	// Sort all the jobs in decreasing order of profit and iterate on jobs these jobs to find slots such that each slot i is empty and i < deadline and i is greatest. Put the job in this slot and mark this slot filled.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n)
	sort(arr.begin(), arr.end(), comparator);
	long long ans[N];
	bool slot[N] = {false};
	for (long long i = 0; i < N; i++) {
		for (long long j = min(N, arr[i][1]) - 1; j >= 0; j--) {
			if (slot[j] == false) {
				ans[j] = i;
				slot[j] = true;
				break;
			}
		}
	}
	for (long long i = 0; i < N; i++) {
		if (slot[i]) {
			cout << arr[ans[i]][0] << " ";
		}
	}
	cout << endl;

	// Method 2:
	// Same procedure but with Disjoint Set Union(DSU). This method can be difficult to understand.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n)
	sort(arr.begin(), arr.end(), comparator);
	long long max_end = find_max(arr, N);
	DisjointSet ds(max_end);
	for (long long i = 0; i < N; i++) {
		long long available_slot = ds.find(arr[i][1]);
		if (available_slot > 0) {
			// This slot is taken by this job 'i' so we need to update the greatest free slot. Note that, in merge, we make first parameter as parent of second parameter.
			// So future queries for available_slot will return maximum available slot in set of "available_slot - 1"
			ds.merge(ds.find(available_slot - 1), available_slot);
			cout << arr[i][0] << " ";
		}
	}
	cout << endl;
	return 0;
}