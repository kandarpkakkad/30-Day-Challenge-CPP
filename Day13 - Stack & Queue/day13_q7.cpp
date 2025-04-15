#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/next-greater-element-i
	https://leetcode.com/problems/next-greater-element-ii/
	https://leetcode.com/problems/next-greater-element-iii/

	You need to run methods for different links differently. See to it that input format is matched.

	Input (link 1):
	3 4
	4 1 2
	1 3 4 2

	Output (link 1):
	3 4
	4 1 2
	1 3 4 2

	Input (link 2):
	3
	1 2 1

	Output (link 2):
	2 -1 2
	2 -1 2

	Input (link 3):
	12

	Output (link 3):
	21

	Input (link 3):
	21

	Output (link 3):
	-1
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long arr1[N], arr2[M];
	for (long long i = 0; i < N; i++) {
		cin >> arr1[i];
	}
	for (long long i = 0; i < M; i++) {
		cin >> arr2[i];
	}

	// Method 1 (link 1):
	// For everynumber in arr2 we will find number greater than that number after that number. The we will search for those greater numbers if the numbers exists in arr1.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	stack<long long> st;
	unordered_map<long long, long long> mp;
	for (long long i = 0; i < M; i++) {
		while (!st.empty() && st.top() < arr2[i]) {
			mp[st.top()] = arr2[i];
			st.pop();
		}
		st.push(arr2[i]);
	}
	long long ans[N];
	for (long long i = 0; i < N; i++) {
		ans[i] = mp.count(arr1[i]) ? mp[arr1[i]] : -1;
	}
	for (long long i = 0; i < N; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

	// Method 1 (link 2):
	// We will use exact method as above but we instead of arr2 we will use arr1.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	stack<long long> st;
	unordered_map<long long, long long> mp;
	for (long long i = 0; i < N; i++) {
		while (!st.empty() && st.top() < arr1[i]) {
			mp[st.top()] = arr1[i];
			st.pop();
		}
		st.push(arr1[i]);
	}
	long long ans[N];
	for (long long i = 0; i < N; i++) {
		ans[i] = mp.count(arr1[i]) ? mp[arr1[i]] : -1;
	}
	for (long long i = 0; i < N; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

	// Method 2 (link 2):
	// We will traverse arr1 2*N times and perform the same thing without map. Here we store the index of array.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	while (!st.empty()) {
		st.pop();
	}
	for (long long i = 0; i < N * 2; i++) {
		while (!st.empty() && arr1[st.top()] < arr1[i % N]) {
			ans[st.top()] = arr1[i % N];
			st.pop();
		}
		st.push(i % N);
	}
	for (long long i = 0; i < N; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

	// Method 1 (link 3):
	// We find next permuation of the string input. If last permutation is enetered output -1.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	string s = to_string(N);
	next_permutation(s.begin(), s.end());
	if (stoi(s) > N) {
		cout << s << endl;
	}
	else {
		cout << -1 << endl;
	}
	return 0;
}