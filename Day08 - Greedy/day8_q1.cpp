#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/meeting-rooms/

	Input:
	3
	0 30
	5 10
	15 20

	Output:
	No
*/

bool comparator(pair<long long, long long> a, pair<long long, long long> b) {
	return a.first < b.first;
}

bool overlap(pair<long long, long long> a, pair<long long, long long> b) {
	return a.second > b.first;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	vector<pair<long long, long long>> intervals;
	long long x, y;
	for (long long i = 0; i < N; i++) {
		cin >> x >> y;
		intervals.push_back({x, y});
	}

	// Method 1:
	// We sort the pairs of start and end by starting time and see if the adjacent pairs overlap. If they overlap, these meetings cannot take place and if it doesn't overlap, the meetings can take place.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	sort(intervals.begin(), intervals.end(), comparator);
	bool flag = true;
	for (long long i = 0; i < N - 1; i++) {
		if (overlap(intervals[i], intervals[i + 1])) {
			flag = false;
			break;
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}
