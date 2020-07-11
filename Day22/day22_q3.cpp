#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/kth-largest-element-in-a-stream/

	Input:
	9 3  ---------------------------> k = 3
	a 4  --------> 4                    4
	a 5  --------> 4 5                  4
	a 8  --------> 4 5 8                4
	a 2  --------> 2 4 5 8              4
	a 3  --------> 2 3 4 5 8            4
	a 5  --------> 2 3 4 5 5 8          5
	a 10 --------> 2 3 4 5 5 8 10       5
	a 9  --------> 2 3 4 5 5 8 9 10     8
	a 4  --------> 2 3 4 4 5 5 8 9 10   8

	Output:
	4
	4
	4
	4
	4
	5
	5
	8
	8
*/

long long add_num(long long k, long long x, priority_queue<long long, vector<long long>, greater<long long>> &pq) {
	if (pq.size() < k || x > pq.top()) {
		pq.push(x);
	}
	if (pq.size() > k) {
		pq.pop();
	}
	return pq.top();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k, x;
	cin >> N >> k;
	char choice;

	// Method 1:
	// We will keep a prioity queue to store the numbers in decreasing order and print the kth element.
	// Time Complexity: O(n)
	// Space Complexity: O(k)
	priority_queue<long long, vector<long long>, greater<long long>> pq;
	while (N--) {
		cin >> choice;
		switch (choice) {
		case 'a':
			cin >> x;
			cout << add_num(k, x, pq) << endl;
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	}
	return 0;
}