#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/delete-node-in-a-linked-list/

	Input:
	6
	0 1 3 5 6 7

	Output:
	7 6 5 3 1 0 -- original
	6 5 3 1 0 -- head
	6 3 1 0 -- head->next
	6 1 0 -- head->next
	6 0 -- head->next
*/

struct node {
	long long val;
	struct node *next;
} *head, *temp, *NEW;

void delete_node(struct node *n) {
	*n = *n->next;
}

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
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;

	// Method 1:
	// We change the value of node to that of the node after that and change the link of the node to the link of next node.
	// Time Complexity: O(1)
	// Space Complexity: O(1)
	struct node *a1, *a2, *a3, *a4;
	a1 = head;
	delete_node(a1);
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	a2 = head->next;
	delete_node(a2);
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	a3 = head->next;
	delete_node(a3);
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	a4 = head->next;
	delete_node(a4);
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}