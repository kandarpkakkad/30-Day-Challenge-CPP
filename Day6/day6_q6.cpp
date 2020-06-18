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
	long long N, k;
	cin >> N >> k;
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
	// Left Shift by counting k elements from starting and adding it back after last element.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	cout << "Left Shift" << endl;
	if (k != 0) {
		struct node *curr = head;
		long long cnt = 1;
		while (cnt < k && curr) {
			curr = curr->next;
			cnt++;
		}
		if (curr != NULL) {
			struct node *kthnode = curr;
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = head;
			head = kthnode->next;
			kthnode->next = NULL;
		}
	}
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;


	// Method 1:
	// Right Shift by counting k elements from starting and adding it back after last element.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	cout << "Right Shift" << endl;
	long long total = 0;
	temp = head;
	while (temp) {
		temp = temp->next;
		total++;
	}
	k = total - k;
	if (k != 0) {
		struct node *curr = head;
		long long cnt = 1;
		while (cnt < k && curr) {
			curr = curr->next;
			cnt++;
		}
		if (curr != NULL) {
			struct node *kthnode = curr;
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = head;
			head = kthnode->next;
			kthnode->next = NULL;
		}
	}

	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}