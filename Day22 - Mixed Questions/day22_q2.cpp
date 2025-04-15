#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/find-median-from-data-stream/

	Input:
	7
	a 4
	a 2
	m   ----------> 2-4
	a 6
	m   ----------> 2-4-6
	a 3
	m   ----------> 2-3-4-6

	Output:
	3
	4
	3.5
*/

void add_num(long long num, priority_queue<long long> &small, priority_queue<long long> &large) {
	small.push(num);
	large.push(-small.top());
	small.pop();
	if (small.size() < large.size()) {
		small.push(-large.top());
		large.pop();
	}
}

double find_median(priority_queue<long long> &small, priority_queue<long long> &large) {
	return small.size() > large.size() ? small.top() : (small.top() - large.top()) / 2.0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, x;
	cin >> N;
	char choice;
	double ans;

	// Method 1:
	// I keep two heaps (or priority queues):
	// 1. Max-heap small has the smaller half of the numbers.
	// 2. Min-heap large has the larger half of the numbers.
	// This gives me direct access to the one or two middle values (they're the tops of the heaps), so getting the median takes O(1) time. And adding a number takes O(log n) time.
	// Supporting both min- and max-heap is more or less cumbersome, depending on the language, so I simply negate the numbers in the heap in which I want the reverse of the default order.
	// Time Complexity: O(log(n)) for adding and O(1) for finding median
	// Space Complexity : O(n)
	priority_queue<long long> small, large;
	while (N--) {
		cin >> choice;
		switch (choice) {
		case 'a':
			cin >> x;
			add_num(x, small, large);
			break;
		case 'm':
			ans = find_median(small, large);
			cout << ans << endl;
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	}
	return 0;
}