#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/implement-stack-using-queues/

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
	5
	8
	5
	20
	23
	20
	Peek: 20
	20
	No
	20
	5
*/

class Stack {
	queue<long long> q, temp;
	long long T;
public:
	Stack() {
		T = 0;
	}

	void push(long long x) {
		T++;
		temp.push(x);
		while (!q.empty()) {
			temp.push(q.front());
			q.pop();
		}
		queue<long long> temp2 = q;
		q = temp;
		temp = temp2;
	}

	void pop() {
		if (q.empty()) {
			return;
		}
		q.pop();
		T--;
	}

	long long top() {
		if (q.empty()) {
			return -1;
		}
		return q.front();
	}

	long long peek() {
		if (q.empty()) {
			return -1;
		}
		return q.front();
	}

	long long is_empt() {
		return (T <= 0);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	Stack s;
	long long N, q;
	cin >> N >> q;
	long long T = -1;
	cout << "Enter\n'i' -> insert\n'd' -> deleten\n'p' -> peek\n'e' -> is_empty\n";
	while (q--) {
		char choice;
		long long x;
		cin >> choice;
		switch (choice) {
		case 'i':
			cin >> x;
			s.push(x);
			break;
		case 'd':
			s.pop();
			break;
		case 'p':
			cout << "Peek: " << s.peek() << endl;
			break;
		case 'e':
			if (s.is_empt()) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}
			break;
		default:
			cout << "Invalid Input" << endl;
			break;
		}
		cout << s.top() << endl;
	}
	return 0;
}