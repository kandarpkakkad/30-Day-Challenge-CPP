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
	temp = head;
	while (temp != NULL) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	struct node *slow, *fast;
	slow = head;
	fast = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	cout << "Middle Element: " << slow->val << endl;
	return 0;
}