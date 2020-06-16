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
	long long N, p;
	cin >> N >> p;
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
	// Count total elements and traverse to total - position and delete that node.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long total = 0;
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		total++;
		temp = temp->next;
	}
	cout << endl;
	long long cnt = 1, fin = total - p;
	temp = head;
	while (cnt < fin && temp) {
		temp = temp->next;
		cnt++;
	}
	temp->next = temp->next->next;
	temp = head;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}