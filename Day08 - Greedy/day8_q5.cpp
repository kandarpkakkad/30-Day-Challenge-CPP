#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/minimum-number-platforms-required-railwaybus-station/

	Input:
	6
	900 940 950 1100 1500 1800
	910 1200 1120 1130 1900 2000

	Output:
	3
	3
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long arr[N], dep[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}
	for (long long i = 0; i < N; i++) {
		cin >> dep[i];
	}

	// Method 1:
	// Find the maximum number of consecutive intersection or overlaps.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	long long ans = 1, plat = 1;
	for (long long i = 0; i < N; i++) {
		plat = 1;
		for (long long j = i + 1; j < N; j++) {
			if ((arr[i] >= arr[j] && arr[i] <= dep[j]) || (arr[j] >= arr[i] && arr[j] <= dep[i])) {
				plat++;
			}
		}
		ans = max(plat, ans);
	}
	cout << ans << endl;

	// Method 2:
	// Perform the same task but differently i.e. 2 pointers.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	sort(arr, arr + N);
	sort(dep, dep + N);
	plat = 1;
	ans = 1;
	long long i = 1, j = 0;
	while (i < N && j < N) {
		if (arr[i] <= dep[j]) {
			plat++;
			i++;
		}
		else {
			plat--;
			j++;
		}
		ans = max(plat, ans);
	}
	cout << ans << endl;
	return 0;
}