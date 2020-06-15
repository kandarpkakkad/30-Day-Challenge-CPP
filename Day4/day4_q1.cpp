#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, x;
	cin >> N >> x;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// We first sort the array and then we keep two pointers one at the beginnning and one at the last number smaller than x. Then we add them and see if sum is equal, greater or smaller than x and act accordingly.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(1)
	sort(arr, arr + N);
	long long pos1 = 0, pos2 = N - 1;
	while (arr[pos2] > x && pos2 > 0) {
		pos2--;
	}
	if (pos2 <= 0) {
		cout << -1 << endl;
	}
	else {
		while (pos1 < pos2) {
			if (arr[pos1] + arr[pos2] == x) {
				break;
			}
			else if (arr[pos1] + arr[pos2] > x) {
				pos2--;
			}
			else {
				pos1++;
			}
		}
		if (pos1 >= pos2) {
			cout << -1 << endl;
		}
		else {
			cout << pos1 + 1 << " " << pos2 + 1 << endl;
		}
	}
	// Method 2:
	// We keep a dictionary to save key->value pairs and search it to find the sum.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	unordered_map<long long, long long> dic;
	bool flag = false;
	long long ans1 = 0, ans2 = 0;
	for (long long i = 0; i <  N; i++) {
		if (dic.find(x - arr[i]) != dic.end() && dic[x - arr[i]] != i) {
			flag = true;
			ans1 = dic[x - arr[i]];
			ans2 = i;
			break;
		}
		dic[arr[i]] = i;
	}
	if (flag) {
		cout << ans1 + 1 << " " << ans2 + 1 << endl;
	}
	else {
		cout << -1 << endl;
	}
	return 0;
}