#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/symmetric-tree

	Input:
	7
	1 2 2 3 4 4 3

	Output:
	Yes
	Yes
*/

struct node {
	long long key;
	struct node *left, *right;
	node (long long x) {
		key = x;
		left = right = NULL;
	}
} *root, *temp, *NEW;

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

bool is_symmetric(struct node *left, struct node *right) {
	if (!left && !right) {
		return true;
	}
	if (!left || !right) {
		return false;
	}
	if (left->key == right->key) {
		return is_symmetric(left->left, right->right) && is_symmetric(left->right, right->left);
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long x;
	root = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		if (!root) {
			NEW = new node(x);
			root = NEW;
		}
		else {
			insert_node(root, x);
		}
	}

	// Method 1:
	// Iterative method. We will compare left of right subtree with right of left subtree and left of left subtree with right of right subtree.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	bool flag = true;
	stack<struct node *> st;
	st.push(root->left);
	st.push(root->right);
	while (!st.empty()) {
		struct node *n1 = st.top();
		st.pop();
		struct node *n2 = st.top();
		st.pop();
		if (!n1 && !n2) {
			continue;
		}
		if (!n1 || !n2 || n1->key != n2->key) {
			flag = false;
			break;
		}
		st.push(n1->left);
		st.push(n2->right);
		st.push(n1->right);
		st.push(n2->left);
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// We will follow the same procedure but with recursion.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	if (is_symmetric(root->left, root->right)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}