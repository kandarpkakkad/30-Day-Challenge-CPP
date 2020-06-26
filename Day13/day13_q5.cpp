#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/implement-queue-using-stacks/

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
	front: 5   back: 5
	front: 5   back: 8
	front: 8   back: 8
	front: 8   back: 20
	front: 8   back: 23
	Back: 23
	front: 8   back: 23
	Front: 8
	front: 8   back: 23
	No
	front: 8   back: 23
	front: 20   back: 23
*/

class Queue {
	stack<long long> s, temp;
public:
	void push(long long x) {
		while (!s.empty()) {
			temp.push(s.top());
			s.pop();
		}
		s.push(x);
		while (!temp.empty()) {
			s.push(temp.top());
			temp.pop();
		}
	}

	long long pop() {
		if (s.empty()) {
			cout << "Queue is empty." << endl;
			return -1;
		}
		long long x = s.top();
		s.pop();
		return x;
	}

	long long front() {
		if (s.empty()) {
			return -1;
		}
		return s.top();
	}

	long long back() {
		long long x;
		if (s.empty()) {
			return -1;
		}
		while (!s.empty()) {
			temp.push(s.top());
			x = s.top();
			s.pop();
		}
		while (!temp.empty()) {
			s.push(temp.top());
			temp.pop();
		}
		return x;
	}

	bool is_empt() {
		return s.empty();
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	Queue q;
	while (M--) {
		char choice;
		long long x;
		cin >> choice;
		switch (choice) {
		case 'i':
			cin >> x;
			q.push(x);
			break;
		case 'd':
			q.pop();
			break;
		case 'f':
			cout << "Front: " << q.front() << endl;
			break;
		case 'b':
			cout << "Back: " << q.back() << endl;
			break;
		case 'e':
			if (q.is_empt()) {
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
		cout << "front: " << q.front() << "   back: " << q.back() << endl;
	}
	return 0;
}