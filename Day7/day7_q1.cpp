#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/merge-two-sorted-lists/

	Input:
	6 5
	6 5 4 3 2 1
	5 4 3 2 1

	Output:
	List 1
	1 2 3 4 5 6

	List 2
	1 2 3 4 5

	Merged List
	1 1 2 2 3 3 4 4 5 5 6
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
	cout << "List 1" << endl;
	temp = head1;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl << endl;
	cout << "List 2" << endl;
	temp = head2;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl << endl;

	// Method 1:
	// The method is same as Day 5, Question 3. We will use 2 pointers to change the links of sorted linked list to merge them.
	// Time Complexity: O(n + m)
	// Space Complexity: O(1)
	cout << "Merged List" << endl;
	struct node *hf, *prev, *h1, *h2;
	hf = (struct node *)malloc(sizeof(struct node));
	hf->val = -1;
	hf->next = NULL;
	prev = hf;
	h1 = head1;
	h2 = head2;
	while (h1 || h2) {
		if (!h1 && h2) {
			prev->next = h2;
			h2 = h2->next;
		}
		else if (!h2 && h1) {
			prev->next = h1;
			h1 = h1->next;
		}
		else {
			if (h1->val <= h2->val) {
				prev->next = h1;
				h1 = h1->next;
			}
			else {
				prev->next = h2;
				h2 = h2->next;
			}
		}
		prev = prev->next;
	}
	hf = hf->next;
	temp = hf;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}