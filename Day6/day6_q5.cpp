#include<bits/stdc++.h>

using namespace std;

struct node {
	long long val;
	struct node *next;
	struct node *down;
} *head1, *head2, *head3, *temp, *NEW;

struct node* flatten_list(struct node *head) {
	struct node *curr = head;
	while (curr) {
		if (curr->down) {
			struct node *post = curr->next;
			struct node *below = flatten_list(curr->down);
			curr->next = below;
			curr->down = NULL;
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = post;
		}
		if (curr->next != NULL) {
			curr = curr->next;
		}
		else {
			break;
		}
	}
	return head;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M, O;
	cin >> N;
	long long x;
	head1 = NULL;
	head2 = NULL;
	head3 = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head1;
		NEW->down = NULL;
		head1 = NEW;
	}
	cin >> M;
	for (long long i = 0; i < M; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head2;
		NEW->down = NULL;
		head2 = NEW;
	}
	cin >> O;
	for (long long i = 0; i < O; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head3;
		NEW->down = NULL;
		head3 = NEW;
	}
	struct node *slow, *fast;
	slow = head1;
	fast = head1;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	slow->down = head2;
	slow = head2;
	fast = head2;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	slow->down = head3;
	// Structure:
	// 1-2-3-4-5-6
	//     |
	//     7-8-9-10
	//       |
	//       11-12

	// Method 1:
	// Recursive method to flatten the list. We traverse till we don't get down as not null and then traverse the down list and repeat the same procedure.
	// Time Complexity: O(n + m + o)
	// Space Complexity: O(1)
	struct node *flattened_list = flatten_list(head1);
	temp = flattened_list;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}