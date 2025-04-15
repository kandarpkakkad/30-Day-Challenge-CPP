#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/longest-common-prefix/

	Input:
	3
	flower
	flow
	flight

	Output:
	fl

	Input:
	3
	dog
	car
	race

	Output:
	"" // Empty String
*/

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	string arr[N];
	for (long long i = 0; i < N; i++) {
		cin >> arr[i];
	}

	string prefix = "";
	bool flag = false;
	long long j = 0;
	if (N == 0) {
		cout << prefix << endl;
	}
	else if (N == 1) {
		cout << arr[0] << endl;
	}
	else {
		while (true) {
			for (long long i = 1; i < N; i++) {
				if (arr[i - 1][j] != arr[i][j]) {
					flag = true;
					break;
				}
			}
			if (flag) {
				break;
			}
			j++;
		}
		for (long long i = 0; i < j; i++) {
			prefix += arr[0][i];
		}
		cout << prefix << endl;
	}
	return 0;
}