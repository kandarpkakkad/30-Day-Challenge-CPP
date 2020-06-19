#include<bits/stdc++.h>

using namespace std;

struct node {
	long long val;
	struct node *next;
} *head1, *head2, *temp, *NEW;

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N >> M;
	head1 = NULL;
	head2 = NULL;
	long long x;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head1;
		head1 = NEW;
	}
	for (long long i = 0; i < M; i++) {
		cin >> x;
		NEW = (struct node *)malloc(sizeof(struct node));
		NEW->val = x;
		NEW->next = head2;
		head2 = NEW;
	}
	struct node *h1, *h2;
	h1 = head1;
	h2 = head2;
	long long cnt = 0;
	while (cnt < M && h1) {
		h1 = h1->next;
		cnt++;
	}
	while (h2->next) {
		h2 = h2->next;
	}
	h2->next = h1;
	long long total = 0;
	temp = head1;
	while (temp) {
		total++;
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
	temp = head2;
	while (temp) {
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;

	// Method 1:
	// We traverse through every element in list 1 for every element in list 2 to check if the meet somewhere.
	// Time Complexity: O(n^2)
	// Space Complexity: O(1)
	h1 = head1;
	h2 = head2;
	bool flag = false;
	while (h2) {
		h1 = head1;
		while (h1) {
			if (h1 == h2) {
				flag = true;
				break;
			}
			h1 = h1->next;
		}
		if (flag) {
			break;
		}
		h2 = h2->next;
	}
	if (flag) {
		cout << "Joining point is " << h2->val << "." << endl;
	}
	else {
		cout << "No joining point." << endl;
	}

	// Method 2:
	// We calculate the sum of all the elements of list 1 and add 1 to all the elements of list 2. Then again calculate sum of elements of list 1 and subtract the old sum to know the position of joining element.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long old_sum = 0, new_sum = 0;
	temp = head1;
	while (temp != NULL) {
		old_sum += temp->val;
		temp = temp->next;
	}
	temp = head2;
	while (temp) {
		temp->val++;
		temp = temp->next;
	}
	temp = head1;
	while (temp != NULL) {
		new_sum += temp->val;
		temp = temp->next;
	}
	long long pos = total - (new_sum - old_sum);
	if (pos == 0) {
		cout << "No Joining Point." << endl;
	}
	else {
		long long d = 0;
		temp = head1;
		while (d < pos && temp) {
			d++;
			temp = temp->next;
		}
		cout << "Joining point is " << temp->val - 1 << "." << endl;
	}

	// Method 3:
	// Find the difference of number of node in both the lists. and traverse bigger list difference number of times. Then traverse both list in parallel to find the common node.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long n = 0, m = 0;
	struct node *a = head1, *b = head2;
	h1 = head1;
	h2 = head2;
	while (h1) {
		h1 = h1->next;
		n++;
	}
	while (h2) {
		h2 = h2->next;
		m++;
	}
	if (n - m > 0) {
		long long p = n - m;
		while (p--) {
			a = a->next;
		}
	}
	else {
		long long p = m - n;
		while (p--) {
			b = b->next;
		}
	}
	while (a && b && a != b) {
		a = a->next;
		b = b->next;
	}
	if (!a || !b) {
		cout << "No joining point." << endl;
	}
	else {
		cout << "Joining point is " << a->val << endl;
	}
	return 0;
}