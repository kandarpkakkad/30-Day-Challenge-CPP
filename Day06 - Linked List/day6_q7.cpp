#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/copy-list-with-random-pointer/

	Input:
	6
	1 4 3 2 5 6
	  ^ ^	  ^
	|_|_|_____|
	  |_|_____|
	  |_|


	Output:
	Traversing through random
	6 1 5 3
	Traversing through next
	6 5 2 3 4 1
*/

struct node {
	long long val;
	struct node *next;
	struct node *random;
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
		NEW->random = NULL;
		head = NEW;
	}
	// Making of data. (You can create your own data)
	struct node *a1, *a2, *a3;
	a1 = head->next;
	a2 = head->next->next->next;
	a3 = head->next->next->next->next->next;
	head->random = a3;
	a3->random = a1;
	a1->random = a2;

	// Method 1:
	// Create a copy of linked list with the next pointers as well and merge with original linked list. Then set the random pointers if in the original list, to the same in copied list. Then separate the two and store the copied in ans.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	struct node *curr = head, *ans;
	while (curr) {
		temp = (struct node *)malloc(sizeof(struct node));
		temp->val = curr->val;
		temp->next = curr->next;
		curr->next = temp;
		curr = temp->next;
	}
	curr = head;
	while (curr) {
		if (curr->random) {
			curr->next->random = curr->random->next;
		}
		curr = curr->next->next;
	}
	curr = head;
	ans = curr->next;
	temp = ans;
	while (curr) {
		curr->next = temp->next;
		curr = curr->next;
		curr ? temp->next = curr->next : 0;
		temp = temp->next;
	}
	head = ans;
	cout << "Traversing through random" << endl;
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->random;
	}
	cout << endl;
	cout << "Traversing through next" << endl;
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	// Random is saved as it is whough we did not know what random pointer points to.
	return 0;
}