#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/linked-list-cycle/

	You need to run the methods one by one.

	Input:
	8
	5 4 3 2 1 6 7 8

	Output:
	2 is the loop starting node.
	8 7 6 1 2 3 4 5
	2 is the loop starting node.
	8 7 6 1 2 3 4 5

*/

struct node {
	long long val;
	struct node *next;
} *head, *temp, *NEW;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long x;
	head = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head;
		head = NEW;
	}
	// Loop
	temp = head;
	struct node *loop = head;
	struct node *fast = head;
	while (temp->next) {
		temp = temp->next;
	}
	while (fast && fast->next) {
		loop = loop->next;
		fast = fast->next->next;
	}
	temp->next = loop;

	// Method 1;
	// We keep counter for each node and if the counter is 2 it is out starting point of loop and then to remove it we traverse from that node and if the node appears again, we set the link of previous node to null.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	map<struct node*, long long> mp;
	temp = head;
	while (temp) {
		if (mp[temp] == 1) {
			break;
		}
		mp[temp] = 1;
		temp = temp->next;
	}
	if (temp == NULL) {
		cout << "No Loop" << endl;
	}
	else {
		cout << temp->val << " is the loop starting node." << endl;
		struct node *save = temp;
		while (temp->next != save) {
			temp = temp->next;
		}
		temp->next = NULL;
		temp = head;
		while (temp) {
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	// Method 2:
	// 2 pointer solution. One will move faster and when again two pointer traversal will give the starting of the loop.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *slow;
	slow = head;
	fast = head;
	while (slow && fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			break;
		}
	}
	if (fast == NULL || fast->next == NULL) {
		cout << "No Loop" << endl;
	}
	else {
		temp = head;
		while (temp) {
			if (slow == temp) {
				break;
			}
			slow = slow->next;
			temp = temp->next;
		}
		if (temp == NULL) {
			cout << "No Loop." << endl;
		}
		else {
			cout << temp->val << " is the loop starting node." << endl;
			struct node *save = temp;
			while (temp->next != save) {
				temp = temp->next;
			}
			temp->next = NULL;
			temp = head;
			while (temp) {
				cout << temp->val << " ";
				temp = temp->next;
			}
			cout << endl;
		}
	}
	return 0;
}
