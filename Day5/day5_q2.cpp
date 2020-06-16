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
	long long cnt = 0;
	temp = head;
	while (temp != NULL) {
		cout << temp->val << " ";
		cnt++;
		temp = temp->next;
	}
	cout << endl;

	// Method 1:
	// We keep 2 pointers 1 will go fast(jump 2 steps) and other slow(jump 1 step) so that slow reaches the middle point when fast reaches end.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *slow, *fast;
	slow = head;
	fast = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	cout << "Middle Element: " << slow->val << endl;

	// Method 2:
	// We keep counter and go till number of elements / 2 to reach middle element.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long t = 0;
	temp = head;
	while (t < cnt / 2 && temp) {
		temp = temp->next;
		t++;
	}
	cout << "Middle Element: " << temp->val << endl;
	return 0;
}