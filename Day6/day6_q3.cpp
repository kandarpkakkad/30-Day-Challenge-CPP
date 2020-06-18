#include<bits/stdc++.h>

using namespace std;

struct node {
	long long val;
	struct node *next;
} *head, *temp, *NEW;

struct node* reversek(struct node *head, long long k) {
	if (!head) {
		return head;
	}
	struct node *pre, *curr, *post;
	curr = head;
	long long total = 0;
	while (curr) {
		curr = curr->next;
		total++;
		if (total >= k) {
			break;
		}
	}
	if (total < k) {
		return head;
	}
	curr = head;
	pre = NULL;
	long long cnt = k;
	while (cnt && curr) {
		post = curr->next;
		curr->next = pre;
		pre = curr;
		curr = post;
		cnt--;
	}
	if (head != NULL) {
		head->next = reversek(post, k);
	}
	return pre;
}

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

	// Method 1:
	// We take from one node to next k nodes and reverse it recursively.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *ans = reversek(head, k);
	struct node *pre, *curr, *post;
	pre = NULL;
	curr = ans;
	post = ans->next;
	while (curr != NULL) {
		curr->next = pre;
		pre = curr;
		curr = post;
		if (curr) {
			post = post->next;
		}
	}
	ans = pre;
	temp = ans;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}