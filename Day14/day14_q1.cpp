#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/next-smaller-element/

	Input:
	5
	4 8 5 2 25

	Output:
	2 5 2 -1 -1
	5 2 2 -1 -1
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// For every element we will check next smallest number in the array.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	long long next;
	for (long long i = 0; i < N; i++) {
		next = -1;
		for (long long j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				next = arr[j];
				break;
			}
		}
		cout << next << " ";
	}
	cout << endl;

	// Method 2:
	// We will find smallest number after all numbers using stack by popping the greater number after after that number.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	stack<long long> s;
	s.push(arr[0]);
	for (long long i = 1; i < N; i++) {
		if (s.empty()) {
			s.push(arr[i]);
			continue;
		}
		while (!s.empty() && s.top() > arr[i]) {
			cout << arr[i] << " ";
			s.pop();
		}
		s.push(arr[i]);
	}
	while (!s.empty()) {
		cout << -1 << " ";
		s.pop();
	}
	cout << endl;
	return 0;
}