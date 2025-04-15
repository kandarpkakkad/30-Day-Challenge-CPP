#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/min-stack/

	Input:
	7
	1 -2
	1 0
	1 -3
	3
	2
	4
	3

	Output:
	-2
	0
	-3
	-3
	NULL
	0
	-2
*/

stack<long long> s1;
stack<long long> s2;

long long getMin() {
	if (s2.empty()) {
		return LLONG_MIN;
	}
	return s2.top();
}

void push(long long x) {
	s1.push(x);
	if (s2.empty() || x <= getMin()) {
		s2.push(x);
	}
}

void pop() {
	if (s1.top() == getMin()) {
		s2.pop();
	}
	s1.pop();
}

long long top() {
	if (!s1.empty()) {
		return s1.top();
	}
	return LLONG_MIN;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long q;
	cin >> q;
	long long s;
	long long x;
	while (q--) {
		cin >> s;
		switch (s) {
		case 1:
			cin >> x;
			push(x);
			cout << x << endl;
			break;
		case 2:
			pop();
			cout << "NULL" << endl;
			break;
		case 3:
			cout << getMin() << endl;
			break;
		case 4:
			cout << top() << endl;
			break;
		default:
			cout << "Invalid Choise" << endl;
			break;
		}
	}
	return 0;
}