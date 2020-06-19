#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/reverse-nodes-in-k-group/

	You need to run the methods one by one.

	Input:
	5 2
	5 4 3 2 1

	Output:
	2 1 4 3 5
	2 1 4 3 5
*/

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

struct node * reversek_2(struct node *head, long long k) {
	struct node *curr, *prev, *post;
	curr = head;
	prev = NULL;
	long long i = k;
	while (curr && i--) {
		post = curr->next;
		curr->next = prev;
		prev = curr;
		curr = post;
	}
	if (!curr && i) {
		curr = prev;
		prev = NULL;
		while (curr) {
			post = curr->next;
			curr->next = prev;
			prev = curr;
			curr = post;
		}
		return prev;
	}
	if (post) {
		head->next = reversek_2(post, k);
	}
	return prev;
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
	// struct node *pre, *curr, *post;
	// pre = NULL;
	// curr = ans;
	// post = ans->next;
	// while (curr != NULL) {
	// 	curr->next = pre;
	// 	pre = curr;
	// 	curr = post;
	// 	if (curr) {
	// 		post = post->next;
	// 	}
	// }
	// ans = pre;
	temp = ans;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;

	// Method 2:
	// Recursive method again with same logic but we will check that k elements are there while reversing beccause not having k elements occurs only once. So if that condition occurs we will reverse the reversed list to make it as it was.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	ans = reversek_2(ans, k);
	// pre = NULL;
	// curr = ans;
	// post = ans->next;
	// while (curr != NULL) {
	// 	curr->next = pre;
	// 	pre = curr;
	// 	curr = post;
	// 	if (curr) {
	// 		post = post->next;
	// 	}
	// }
	// ans = pre;
	temp = ans;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}