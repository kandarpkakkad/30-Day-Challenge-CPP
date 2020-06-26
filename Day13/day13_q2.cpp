#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/queue-data-structure/

	Input:
	15 9
	i 5
	i 8
	d
	i 20
	i 23
	b
	f
	e
	d

	Output:
	5
	F: 0   R: 0
	-------
	5 8
	F: 0   R: 1
	-------
	8
	F: 1   R: 1
	-------
	8 20
	F: 1   R: 2
	-------
	8 20 23
	F: 1   R: 3
	-------
	Back: 23
	F: 1   R: 3
	-------
	Front: 8
	F: 1   R: 3
	-------
	No
	F: 1   R: 3
	-------
	20 23
	F: 2   R: 3
	-------
*/

void display(long long q[], long long &F, long long &R, long long N) {
	if (F == -1 || F > R) {
		cout << "No Elements" << endl;
		return;
	}
	for (long long i = F; i <= R; i++) {
		cout << q[i] << " ";
	}
	cout << endl;
}

void push(long long q[], long long &F, long long &R, long long N, long long val) {
	if (R == -1) {
		R = 0;
		F = 0;
		q[R] = val;
	}
	else {
		R++;
		if (R >= N) {
			cout << "Queue Overflow." << endl;
		}
		else {
			q[R] = val;
		}
	}
}

long long pop(long long q[], long long &F, long long &R, long long N) {
	if (F > R) {
		cout << "Queue Underflow" << endl;
		return -1;
	}
	else if (F == R) {
		long long temp = q[F];
		F = -1;
		R = -1;
		return temp;
	}
	else {
		long long temp = q[F];
		F++;
		return temp;
	}
}

long long front(long long q[], long long &F, long long &R, long long N) {
	if (F > R || F < 0) {
		cout << "Empty Queue" << endl;
		return -1;
	}
	else {
		return q[F];
	}
}

long long back(long long q[], long long &F, long long &R, long long N) {
	if (F > R || F < 0) {
		cout << "Empty Queue" << endl;
		return -1;
	}
	else {
		return q[R];
	}
}

bool is_empt(long long q[], long long &F, long long &R, long long N) {
	return (F > R || F < 0);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long Queue[N];
	long long F = -1;
	long long R = -1;
	while (M--) {
		char choice;
		long long x;
		cin >> choice;
		switch (choice) {
		case 'i':
			cin >> x;
			push(Queue, F, R, N, x);
			display(Queue, F, R, N);
			break;
		case 'd':
			pop(Queue, F, R, N);
			display(Queue, F, R, N);
			break;
		case 'f':
			cout << "Front: " << front(Queue, F, R, N) << endl;
			break;
		case 'b':
			cout << "Back: " << back(Queue, F, R, N) << endl;
			break;
		case 'e':
			if (is_empt(Queue, F, R, N)) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}
			break;
		default:
			cout << "Invalid Choice" << endl;
			break;
		}
		cout << "F: " << F << "   R: " << R << endl;
		cout << "-------" << endl;
	}
	return 0;
}