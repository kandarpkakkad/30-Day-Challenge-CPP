#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/stack-data-structure-introduction-program/

	Input:
	15 9
	i 5
	i 8
	d
	i 20
	i 23
	d
	p
	e
	d

	Output:
	Enter
	'i' -> insert
	'd' -> deleten
	'p' -> peek
	'e' -> is_empty
	5
	-------
	8 5
	-------
	5
	-------
	20 5
	-------
	23 20 5
	-------
	20 5
	-------
	Peek: 5
	20 5
	-------
	No
	20 5
	-------
	5
	-------
*/

void display(long long s[], long long &T, long long N) {
	if (T < 0) {
		return;
	}
	else if (T == N) {
		for (long long i = T - 1; i >= 0; i--) {
			cout << s[i] << " ";
		}
		cout << endl;
	}
	else {
		for (long long i = T; i >= 0; i--) {
			cout << s[i] << " ";
		}
		cout << endl;
	}
}

void push(long long s[], long long N, long long &T, long long val) {
	T++;
	if (T < N) {
		s[T] = val;
	}
	else {
		cout << "Stack Overflow." << endl;
	}
}

long long pop(long long s[], long long &T) {
	if (T < 0) {
		cout << "Stack Underflow." << endl;
		return -1;
	}
	else {
		long long temp = s[T];
		T--;
		return temp;
	}
}

bool is_empt(long long s[], long long T) {
	return (T < 0);
}

long long peek(long long s[], long long T, long long N) {
	if (T < 0) {
		return -1;
	}
	return s[T - 1];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, q;
	cin >> N >> q;
	long long Stack[N];
	long long T = -1;
	cout << "Enter\n'i' -> insert\n'd' -> deleten\n'p' -> peek\n'e' -> is_empty\n";
	while (q--) {
		char choice;
		long long x;
		cin >> choice;
		switch (choice) {
		case 'i':
			cin >> x;
			push(Stack, N, T, x);
			display(Stack, T, N);
			break;
		case 'd':
			pop(Stack, T);
			display(Stack, T, N);
			break;
		case 'p':
			cout << "Peek: " << peek(Stack, T, N) << endl;
			display(Stack, T, N);
			break;
		case 'e':
			if (is_empt(Stack, T)) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}
			display(Stack, T, N);
			break;
		default:
			cout << "Invalid Input" << endl;
			break;
		}
		cout << "-------" << endl;
	}
	return 0;
}