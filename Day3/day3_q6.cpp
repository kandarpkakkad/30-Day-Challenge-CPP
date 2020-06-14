#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	/*
	HR Round Puzzles -> https://www.geeksforgeeks.org/puzzles/
	Programming Puzzles -> https://www.geeksforgeeks.org/tag/programming-puzzle/
	Few programming puzzles are solved below.
	*/

	// Q1. Count the number of trailing zeroes in 1^1 * 2^2 * 3^3 * .... * n^n.
	/*
	long long N;
	cin >> N;
	long long cnt2 = 0, cnt5 = 0;
	for (long long i = 1; i <= N; i++) {
		long long temp = i;
		while (temp % 2 == 0 && temp > 0) {
			temp /= 2;
			cnt2 += i; // adding i because of the power
		}
		while (temp % 5 == 0 && temp > 0) {
			temp /= 5;
			cnt5 += i; // adding i because of the power
		}
	}
	long long ans = min(cnt2, cnt5);
	cout << ans << endl;
	*/

	// Q2. Number of wins for each player in a series of Rock-Paper-Scissor
	/*
	long long k;
	cin >> k;
	string a, b;
	cin >> a;
	cin >> b;
	long long N = a.length();
	long long M = b.length();
	long long moves = N * M;
	long long i = 0;
	long long j = 0;
	long long player1_win = 0, player2_win = 0;
	while (moves--) {
		long long res = -3;
		if (a[i] == b[i]) {
			res = 0;
		}
		if (a[i] == 'R') {
			if (b[i] == 'S') {
				res = 1;
			}
			else if (b[i] == 'P') {
				res = -1;
			}
		}
		if (a[i] == 'P') {
			if (b[i] == 'R') {
				res = 1;
			}
			else if (b[i] == 'S') {
				res = -1;
			}
		}
		if (a[i] == 'S') {
			if (b[i] == 'P') {
				res = 1;
			}
			else if (b[i] == 'R') {
				res = -1;
			}
		}
		if (res == 1) {
			player1_win++;
		}
		if (res == -1) {
			player2_win++;
		}
		i = (i + 1) % N;
		j = (j + 1) % M;
	}
	long long repeat = k / (N * M);
	player1_win *= repeat;
	player2_win *= repeat;
	long long remaining = k % (N * M);
	while (remaining--) {
		long long res = -3;
		if (a[i] == b[i]) {
			res = 0;
		}
		if (a[i] == 'R') {
			if (b[i] == 'S') {
				res = 1;
			}
			else if (b[i] == 'P') {
				res = -1;
			}
		}
		if (a[i] == 'P') {
			if (b[i] == 'R') {
				res = 1;
			}
			else if (b[i] == 'S') {
				res = -1;
			}
		}
		if (a[i] == 'S') {
			if (b[i] == 'P') {
				res = 1;
			}
			else if (b[i] == 'R') {
				res = -1;
			}
		}
		if (res == 1) {
			player1_win++;
		}
		if (res == -1) {
			player2_win++;
		}
		i = (i + 1) % N;
		j = (j + 1) % M;
	}
	cout << player1_win << " " << player2_win << endl;
	*/
	return 0;
}