#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/flood-fill/

	Input:
	3 3
	1 1 1
	1 1 0
	1 0 1
	1 1
	2

	Output:
	2 2 2
	2 2 0
	2 0 1
*/

void flood_fill(vector<vector<long long>> &arr, long long sr, long long sc, long long color,  long long new_color) {
	if (sr < 0 || sc < 0 || sr >= arr.size() || sc >= arr[0].size() || arr[sr][sc] != color) {
		return;
	}
	arr[sr][sc] = new_color;
	flood_fill(arr, sr, sc - 1, color, new_color);
	flood_fill(arr, sr, sc + 1, color, new_color);
	flood_fill(arr, sr - 1, sc, color, new_color);
	flood_fill(arr, sr + 1, sc, color, new_color);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, x;
	cin >> N >> M;
	vector<vector<long long>> arr;
	for (long long i = 0; i < N; i++) {
		vector<long long> r;
		for (long long j = 0; j < M; j++) {
			cin >> x;
			r.push_back(x);
		}
		arr.push_back(r);
	}
	long long sr, sc, new_color;
	cin >> sr >> sc;
	cin >> new_color;

	// Method 1:
	// We check all four sides and if any of the sides is a new color and its current color is same as give arr[sr][sc] and is connected to the point, we change the current color to new color.
	// Time Complexity: O()
	// Space Complexity: O(1)
	if (arr[sr][sc] != new_color) {
		flood_fill(arr, sr, sc, arr[sr][sc], new_color);
	}
	for (long long i = 0; i < N; i++) {
		for (long long j = 0; j < M; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}