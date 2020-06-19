#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/linked-list-cycle/

	Input:
	6
	6 5 4 3 2 1 (mid point is the starting of the loop. You can change it your self.)

	Output:
	4 is the starting of the loop.
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
	struct node *slow, *fast;
	slow = head;
	fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	temp = head;
	while (temp->next) {
		temp = temp->next;
	}
	temp->next = slow;
	// cout << slow->val << " will be the starting of the loop." << endl;

	// Method 1:
	// We will use slow and fast pointers to find if there is loop and if there is we will traverse through loop and list simultaneously and their meeting point will be starting of the loop.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	slow = head;
	fast = head;
	while (slow && fast) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			break;
		}
	}
	temp = head;
	while (temp) {
		if (temp == slow) {
			break;
		}
		temp = temp->next;
		slow = slow->next;
	}
	cout << temp->val << " is the starting of the loop." << endl;
	return 0;
}