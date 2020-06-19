#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/add-two-numbers/

	Input:
	3 4
	2 4 7
	5 6 4 2

	Output:
	  7 4 2 0
	+ 2 4 6 5
	= 9 8 8 5
*/

struct node {
	long long val;
	struct node *next;
} *head1, *head2, *temp, *NEW;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	long long x;
	head1 = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head1;
		head1 = NEW;
	}
	head2 = NULL;
	for (long long i = 0; i < M; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head2;
		head2 = NEW;
	}

	// Method 1:
	// We keep carry value and add the numbers and store it in the linked list given.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *h1, *h2;
	h1 = head1;
	while (h1->next) {
		h1 = h1->next;
	}
	h2 = head2;
	while (h2->next) {
		h2 = h2->next;
	}
	if (N > M) {
		for (long long i = 0; i < N - M; i++) {
			NEW = (struct node *)malloc(sizeof(struct node));
			NEW->val = 0;
			NEW->next = NULL;
			h2->next = NEW;
		}
	}
	else if (M > N) {
		for (long long i = 0; i < M - N; i++) {
			NEW = (struct node *)malloc(sizeof(struct node));
			NEW->val = 0;
			NEW->next = NULL;
			h1->next = NEW;
		}
	}
	cout << "  ";
	temp = head1;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	cout << "+ ";
	temp = head2;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;

	long long carry = 0;
	h1 = head1;
	h2 = head2;
	long long r;
	while (h1 && h2) {
		r = carry;
		carry = (h1->val + h2->val + r) / 10;
		h1->val = (h1->val + h2->val + r) % 10;
		h1 = h1->next;
		h2 = h2->next;
	}
	h1 = head1;
	while (h1->next) {
		h1 = h1->next;
	}
	if (carry) {
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = carry;
		NEW->next = NULL;
		h1->next = NEW;
	}
	cout << "= ";
	temp = head1;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}