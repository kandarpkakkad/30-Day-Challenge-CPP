#include<bits/stdc++.h>

using namespace std;

struct node {
	long long val;
	struct node *next;
}*head, *temp, *NEW;

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
	// Method 1:
	// We keep 3 pointers and change the link to previous pointer to reverse the linked list
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	if (head == NULL) {
		cout << "No Elements" << endl;
	}
	else {
		temp = head;
		while (temp != NULL) {
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	struct node *pre, *curr, *post;
	if (head == NULL) {
		cout << "No Elements" << endl;
	}
	else if (head->next == NULL) {
		cout << head->val << endl;
	}
	else {
		pre = NULL;
		curr = head;
		post = head->next;
		while (curr != NULL) {
			curr->next = pre;
			pre = curr;
			curr = post;
			if (curr) {
				post = post->next;
			}
		}
		head = pre;
		temp = head;
		while (temp != NULL) {
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	return 0;
}