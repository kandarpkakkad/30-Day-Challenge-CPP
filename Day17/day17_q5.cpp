#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/print-left-view-binary-tree/
	https://leetcode.com/problems/binary-tree-right-side-view/

	Input:
	10
	7 11 10 15 9 8 12 17 21 24

	Output:
	Left View
	7 11 15 17
	Right View
	7 10 12 24
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

void func_left(struct node *root, long long level, long long *max_level) {
	if (!root) {
		return;
	}
	if (*max_level < level) {
		cout << root->key << " ";
		*max_level = level;
	}
	func_left(root->left, level + 1, max_level);
	// If right->left height is same as left->left then left->left will be printed.
	func_left(root->right, level + 1, max_level);
}

void left_view(struct node *root) {
	long long max_level = 0;
	func_left(root, 1, &max_level);
}

void func_right(struct node *root, long long level, long long *max_level) {
	if (!root) {
		return;
	}
	if (*max_level < level) {
		cout << root->key << " ";
		*max_level = level;
	}
	func_right(root->right, level + 1, max_level);
	// If right->right height is same as left->right then left->right will be printed.
	func_right(root->left, level + 1, max_level);
}

void right_view(struct node *root) {
	long long max_level = 0;
	func_right(root, 1, &max_level);
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

	// Left View Method 1:
	// We recursively traverse through left side until left subtree's height is max and then go right side if right subtree's height is more.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	cout << "Left View" << endl;
	left_view(root);
	cout << endl;

	// Right View Method 1:
	// We recursively traverse through right side until right subtree's height is max and then go left side if left subtree's height is more.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	cout << "Right View" << endl;
	right_view(root);
	cout << endl;
	return 0;
}