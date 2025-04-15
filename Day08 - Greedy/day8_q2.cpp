#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons
	https://en.wikipedia.org/wiki/Activity_selection_problem

	Input:
	7
	9 12
	1 10
	4 11
	8 12
	3 9
	6 9
	6 7

	Output:
	2
*/

bool constructor(pair<long long, long long> a, pair<long long, long long> b) {
	return a.second == b.second ? a.first < b.first : a.second < b.second;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	vector<pair<long long, long long>> arr;
	long long x, y;
	for (long long i = 0; i < N; i++) {
		cin >> x >> y;
		arr.push_back({x, y});
	}

	sort(arr.begin(), arr.end(), constructor);
	// Method 1:
	// Sort the array and find the points greater than the current value for all the values in the array.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	long long mx = LLONG_MIN;
	long long cnt = 0;
	for (long long i = 0; i < N; i++) {
		if (mx != LLONG_MAX && mx >= arr[i].first) {
			continue;
		}
		mx = arr[i].second;
		cnt++;
	}
	cout << cnt << endl;
	return 0;
}