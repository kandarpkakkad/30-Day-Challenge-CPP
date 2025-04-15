#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/fractional-knapsack-problem/

	Input:
	3 50
	60 10
	100 20
	120 30

	Output:
	240
*/

bool comparator(pair<long long, long long> a, pair<long long, long long> b) {
	return a.first / a.second > b.first / b.second; // > because we need it in decreasing order.
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	long long val, w;
	vector<pair<long long, long long>> arr;
	for (long long i = 0; i < N; i++) {
		cin >> val >> w;
		arr.push_back({val, w});
	}

	// Method 1:
	// In this method we are allowed to break items into fractions for maximizing the total value of knapsack. We calculate the ratio value/weight for each item and the item on the basis of this ratio. Then take the item with highest ratio and add them intil we can't add the next item as a whole and at the end add the next item as much as we can.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	sort(arr.begin(), arr.end(), comparator);
	long long currw = 0;
	double ans = 0.0;
	for (long long i = 0; i < N; i++) {
		if (currw + arr[i].second <= k) {
			currw += arr[i].second;
			ans += arr[i].first;
		}
		else {
			long long remain = k - currw;
			ans += arr[i].first * (double(remain) / arr[i].second);
			break;
		}
	}
	cout << ans << endl;
	return 0;
}