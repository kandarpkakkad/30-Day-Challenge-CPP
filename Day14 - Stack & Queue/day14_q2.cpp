#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/lru-cache

	Input:
	5 17
	p 1 1
	g 2
	p 2 2
	p 3 3
	g 2
	p 4 4
	g 1
	g 3
	g 4
	p 5 5
	p 6 6
	p 7 7
	p 8 8
	g 5
	g 1
	g 2
	g 8

	Output:
	Put: 1 --> 1
	1
	Got: 2 --> -1
	1
	Put: 2 --> 2
	2 1
	Put: 3 --> 3
	3 2 1
	Got: 2 --> 2
	2 3 1
	Put: 4 --> 4
	4 2 3 1
	Got: 1 --> 1
	1 4 2 3
	Got: 3 --> 3
	3 1 4 2
	Got: 4 --> 4
	4 3 1 2
	Put: 5 --> 5
	5 4 3 1 2
	Put: 6 --> 6
	6 5 4 3 1
	Put: 7 --> 7
	7 6 5 4 3
	Put: 8 --> 8
	8 7 6 5 4
	Got: 5 --> 5
	5 8 7 6 4
	Got: 1 --> -1
	5 8 7 6 4
	Got: 2 --> -1
	5 8 7 6 4
	Got: 8 --> 8
	8 5 7 6 4
*/

unordered_map<long long, long long> mp;
deque<long long> dq;

long long get(long long key) {
	if (mp.find(key) == mp.end()) {
		return -1;
	}
	else {
		deque<long long>::iterator it = dq.begin();
		while (*it != key) {
			it++;
		}
		dq.erase(it);
		dq.push_front(key);
		return mp[key];
	}
}

void put(long long key, long long value, long long capacity) {
	if (mp.find(key) == mp.end()) {
		if (capacity == dq.size()) {
			long long last = dq.back();
			dq.pop_back();
			mp.erase(last);
		}
	}
	else {
		deque<long long>::iterator it = dq.begin();
		while (*it != key) {
			it++;
		}
		dq.erase(it);
		mp.erase(key);
	}
	dq.push_front(key);
	mp[key] = value;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long capacity, q;
	cin >> capacity >> q;
	deque<long long>::iterator it;
	while (q--) {
		char choice;
		long long key, value;
		cin >> choice;
		switch (choice) {
		case 'p':
			cin >> key >> value;
			put(key, value, capacity);
			cout << "Put: " << key << " --> " << value << endl;
			it = dq.begin();
			if (dq.empty()) {
				cout << "Empty" << endl;
			}
			else {
				while (*it != dq.back()) {
					cout << *it << " ";
					it++;
				}
				cout << dq.back() << endl;
			}
			break;
		case 'g':
			cin >> key;
			cout << "Got: " << key << " --> " << get(key) << endl;
			it = dq.begin();
			if (dq.empty()) {
				cout << "Empty" << endl;
			}
			else {
				while (*it != dq.back()) {
					cout << *it << " ";
					it++;
				}
				cout << dq.back() << endl;
			}
			break;
		default:
			cout << "Invalid Choice" << endl;
			break;
		}
	}
	return 0;
}