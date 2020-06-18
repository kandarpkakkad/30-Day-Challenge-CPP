#include<bits/stdc++.h>

using namespace std;

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

	// Method 1:
	// We traverse the linked list and store it to make it reverse. Then we traverse both simultaneously to check whether it is palindrome or not.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *head_rev;
	temp = head;
	while (temp) {
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = temp->val;
		NEW->next = head_rev;
		head_rev = NEW;
		temp = temp->next;
	}
	temp = head;
	struct node *temp2 = head_rev;
	bool flag = true;
	while (temp && temp2) {
		if (temp->val != temp2->val) {
			flag = false;
			break;
		}
		temp = temp->next;
		temp2 = temp2->next;
	}
	if (flag) {
		cout << "Palindrome" << endl;
	}
	else {
		cout << "Not Palindrome" << endl;
	}

	// Method 2:
	// We reverse half of the linked list and and check is it is equal to rest of the half.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *slow = head, *fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	fast = head;
	struct node *prev = NULL;
	struct node *n;
	while (slow) {
		n = slow->next;
		slow->next = prev;
		prev = slow;
		slow = n;
	}
	slow = prev;
	flag = true;
	while (slow) {
		if (slow->val != fast->val) {
			flag = false;
			break;
		}
		slow = slow->next;
		fast = fast->next;
	}
	if (flag) {
		cout << "Palindrome" << endl;
	}
	else {
		cout << "Not Palindrome" << endl;
	}
	return 0;
}