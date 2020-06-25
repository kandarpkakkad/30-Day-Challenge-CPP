#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/3sum/

	Input:
	6 9
	1 2 3 4 5 6

	Output:
	1 2 6
	1 3 5
	2 3 4
*/

void Print_Vector(set<long long> Vec) {
	for (auto i = Vec.begin(); i != Vec.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	return;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k;
	cin >> N >> k;
	long long arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// Method 1:
	// We will traverse array and and for each element we will find pair with whom the sum is equal to k. We will use set so that there is no redundancy.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	sort(arr, arr + N);
	long long l, r;
	bool flag = false;
	set<set<long long>> ans;
	for (long long i = 0; i < N - 1; i++) {
		l = i + 1;
		r = N - 1;
		while (l < r) {
			set<long long> a;
			if (arr[l] + arr[r] < k - arr[i]) {
				l++;
			}
			else if (arr[l] + arr[r] > k - arr[i]) {
				r--;
			}
			else {
				a.insert(arr[i]);
				a.insert(arr[l]);
				a.insert(arr[r]);
				l++;
				r--;
			}
			if (a.size() == 3) {
				ans.insert(a);
			}
		}
	}
	for (auto i = ans.begin(); i != ans.end(); i++) {
		Print_Vector(*i);
	}
	return 0;
}