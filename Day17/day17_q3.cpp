#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/binary-tree-preorder-traversal/

	Input:
	7
	7 11 10 15 9 8 12

	Output:
	7 11 15 9 10 8 12
	7 11 15 9 10 8 12
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

void preorder_recursive(struct node *root) {
	if (!root) {
		return;
	}
	if (root->key != 1000000000) {
		cout << root->key << " ";
	}
	preorder_recursive(root->left);
	preorder_recursive(root->right);
}

void preorder_iterative(struct node *root) {
	if (!root) {
		return;
	}
	temp = root;
	stack<struct node *> st;
	st.push(root);
	while (!st.empty()) {
		temp = st.top();
		st.pop();
		if (temp->key != 1000000000) {
			cout << temp->key << " ";
		}
		if (temp->right) {
			st.push(temp->right);
		}
		if (temp->left) {
			st.push(temp->left);
		}
	}
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
	// Recursion. We will recursively print the tree in the formate of mid-left-right.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	preorder_recursive(root);
	cout << endl;

	// Method 2:
	// Iteration. We store the next node in stack and print the current node which creates the format of mid-left-right.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	preorder_iterative(root);
	cout << endl;
	return 0;
}