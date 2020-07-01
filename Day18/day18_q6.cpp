#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/same-tree/

	Input:
	9
	1 2 3 7 6 5 4 8 9
	9
	1 2 3 7 6 5 4 8 9

	Output:
	Yes
	Yes

	Input:
	9
	1 2 3 7 6 5 4 8 9
	7
	1 2 3 7 6 5 4

	Output:
	No
	No

	Input:
	9
	1 2 3 7 6 5 4 8 9
	9
	1 2 10 7 15 5 4 8 9

	Output:
	No
	No
*/

struct node {
	long long key;
	struct node *left, *right;
	node (long long x) {
		key = x;
		left = right = NULL;
	}
} *root1, *root2, *temp, *NEW;

void insert_node(struct node *root, long long k) {
	queue<struct node *> q;
	q.push(root);
	while (!q.empty()) {
		struct node *temp = q.front();
		q.pop();
		if (temp->left == NULL) {
			temp->left = new node(k);
			break;
		}
		else {
			q.push(temp->left);
		}
		if (temp->right == NULL) {
			temp->right = new node(k);
			break;
		}
		else {
			q.push(temp->right);
		}
	}
}

void delete_deepest(struct node *root, struct node *d_node) {
	queue<struct node *> q;
	q.push(root);
	while (!q.empty()) {
		struct node *temp = q.front();
		q.pop();
		if (temp == d_node) {
			temp = NULL;
			delete(d_node);
			return;
		}
		if (temp->right) {
			if (temp->right == d_node) {
				temp->right = NULL;
				delete(d_node);
				return;
			}
			else {
				q.push(temp->right);
			}
		}
		if (temp->left) {
			if (temp->left == d_node) {
				temp->left = NULL;
				delete(d_node);
				return;
			}
			else {
				q.push(temp->left);
			}
		}
	}
}

struct node * delete_node(struct node *root, long long k) {
	if (!root) {
		return NULL;
	}
	if (root->left == NULL && root->right == NULL) {
		if (root->key == k) {
			return NULL;
		}
		else {
			return root;
		}
	}
	queue<struct node *> q;
	q.push(root);
	struct node *key_node = NULL;
	while (!q.empty()) {
		temp = q.front();
		q.pop();
		if (temp->key == k) {
			key_node = temp;
		}
		if (temp->left) {
			q.push(temp->left);
		}
		if (temp->right) {
			q.push(temp->right);
		}
	}
	// temp is the last node that is to be added in place of deleted node.
	// key_node is the node to be deleted.
	// So we delete temp node and add its value to key_node.
	if (key_node != NULL) {
		long long x = temp->key;
		delete_deepest(root, temp);
		key_node->key = x;
	}
	return root;
}

bool is_same_tree(struct node *root1, struct node *root2) {
	if (!root1 || !root2) {
		return root1 == root2;
	}
	return (root1->key == root2->key && is_same_tree(root1->left, root2->left) && is_same_tree(root1->right, root2->right));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, M;
	cin >> N;
	long long x;
	root1 = NULL;
	root2 = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		if (!root1) {
			NEW = new node(x);
			root1 = NEW;
		}
		else {
			insert_node(root1, x);
		}
	}
	cin >> M;
	for (long long i = 0; i < M; i++) {
		cin >> x;
		if (!root2) {
			NEW = new node(x);
			root2 = NEW;
		}
		else {
			insert_node(root2, x);
		}
	}

	// Method 1:
	// Recursive method where we check the left and right subtrees whether they are same or not.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	if (is_same_tree(root1, root2)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// We will do the same procedure but without recursion. We use similar method as postorder traversal with iteration.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	struct node *temp1, *temp2;
	bool flag = true;
	stack<struct node *> s1, s2;
	if (root1) {
		s1.push(root1);
	}
	if (root2) {
		s2.push(root2);
	}
	while (!s1.empty() && !s2.empty()) {
		temp1 = s1.top();
		temp2 = s2.top();
		s1.pop();
		s2.pop();
		if (temp1->key != temp2->key) {
			flag = false;
			break;
		}
		if (temp1->right) {
			s1.push(temp1->right);
		}
		if (temp2->right) {
			s2.push(temp2->right);
		}
		if (s1.size() != s2.size()) {
			flag = false;
			break;
		}
		if (temp1->left) {
			s1.push(temp1->left);
		}
		if (temp2->left) {
			s2.push(temp2->left);
		}
		if (s1.size() != s2.size()) {
			flag = false;
			break;
		}
	}
	if (flag == false || s1.size() != s2.size()) {
		cout << "No" << endl;
	}
	else {
		cout << "Yes" << endl;
	}
	return 0;
}