#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/merge-two-sorted-lists/

	Input:
	6 4
	0 1 3 5 6 7
	2 4 8 9

	Output:
	7 6 5 3 1 0
	9 8 4 2
	7 6 5 3 1 0 9 8 4 2
	7 6 5 3 1 0 9 8 4 2
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
	head2 = NULL;
	for (long long i = 0; i < N; i++) {
		NEW = (struct node *)malloc(sizeof(struct node));
		cin >> x;
		NEW->val = x;
		NEW->next = head1;
		head1 = NEW;
	}
	for (long long i = 0; i < M; i++) {
		NEW = (struct node *)malloc(sizeof(struct node));
		cin >> x;
		NEW->val = x;
		NEW->next = head2;
		head2 = NEW;
	}
	temp = head1;
	while (temp != NULL) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	temp = head2;
	while (temp != NULL) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;

	// Method 1:
	// Create new list and add sorted elements. We will get decreasing order list which we will reverse to get the answer.
	// Time Complexity: O(n + m)
	// Space Complexity: O(n + m)
	struct node *head3, *t1, *h1, *h2, *pre, *curr, *post;
	head3 = NULL;
	h1 = head1;
	h2 = head2;
	while (h1 && h2) {
		t1 = (struct node*)malloc(sizeof(struct node));
		if (h1->val < h2->val) {
			t1->val = h1->val;
			h1 = h1->next;
		}
		else if (h1->val >= h2->val) {
			t1->val = h2->val;
			h2 = h2->next;
		}
		t1->next = head3;
		head3 = t1;
	}
	h1 = h1 ? h1 : h2;
	while (h1 != NULL) {
		t1 = (struct node*)malloc(sizeof(struct node));
		t1->val = h1->val;
		h1 = h1->next;
		t1->next = head3;
		head3 = t1;
	}
	pre = NULL;
	curr = head3;
	post = head3->next;
	while (curr != NULL) {
		curr->next = pre;
		pre = curr;
		curr = post;
		if (curr) {
			post = post->next;
		}
	}
	head3 = pre;
	temp = head3;
	while (temp != NULL) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;

	// Method 2:
	// We will keep one auxiliary variable to store min of the two checking and add it in middle of another linked list.
	// Time Complexity: O(n + m)
	// Space Complexity: O(m)
	// if (N == 0 || M == 0) {
	// 	temp = head1 ? head1 : head2;
	// 	while (temp) {
	// 		cout << temp->val << " ";
	// 		temp = temp->next;
	// 	}
	// 	cout << endl;
	// }
	// else {
	// 	struct node *hf, *pnew;
	// 	h1 = head1;
	// 	h2 = head2;
	// 	hf = head1;
	// 	pnew = NULL;
	// 	while (h1 && h2) {
	// 		pnew = (struct node *)malloc(sizeof(struct node));
	// 		if (h1->val == h2->val) {
	// 			pnew->val = h2->val;
	// 			pnew->next = h1->next;
	// 			h1->next = pnew;
	// 			h1 = pnew->next;
	// 			h2 = h2->next;
	// 		}
	// 		else if (h1->val < h2->val) {
	// 			h1 = h1->next;
	// 		}
	// 		else {
	// 			pnew->val = h2->val;
	// 			pnew->next = h1;
	// 			h2 = h2->next;
	// 			hf = pnew;
	// 		}
	// 	}
	// 	h1 = h1 ? h1 : h2;
	// 	h2 = hf ? hf : h1 ? h1 : h2;
	// 	while (h2->next != NULL) {
	// 		h2 = h2->next;
	// 	}
	// 	while (h1 != NULL) {
	// 		pnew = (struct node *)malloc(sizeof(struct node));
	// 		pnew->val = h1->val;
	// 		pnew->next = NULL;
	// 		h2->next = pnew;
	// 		h2 = h2->next;
	// 		h1 = h1->next;
	// 	}
	// 	head1 = hf;
	// 	temp = head1;
	// 	while (temp != NULL) {
	// 		cout << temp->val << " ";
	// 		temp = temp->next;
	// 	}
	// 	cout << endl;
	// }

	// Method 3:
	// We will directly change the links of the linked lists.
	// Time Complexity: O(n + m)
	// Space Complexity: O(1)
	struct node *headf, *prev;
	headf = (struct node *)malloc(sizeof(struct node));
	headf->val = -1;
	headf->next = NULL;
	prev = headf;
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
	headf = headf->next;
	temp = headf;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}