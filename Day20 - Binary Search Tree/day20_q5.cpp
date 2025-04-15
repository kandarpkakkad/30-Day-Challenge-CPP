#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree

	Input:
	7
	4 2 5 3 1 6 7

	Output:
	p: 1   q: 3
	2 is the Least Common Ancestor.
	2 is the Least Common Ancestor.
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
	NEW = new node(k);
	temp = root;
	while (temp) {
		if (k > temp->key) {
			if (temp->right) {
				temp = temp->right;
			}
			else {
				temp->right = NEW;
				return;
			}
		}
		else {
			if (temp->left) {
				temp = temp->left;
			}
			else {
				temp->left = NEW;
				return;
			}
		}
	}
}

void delete_node(long long k) {
	if (!root) {
		return;
	}
	temp = root;
	bool flag = false;
	while (temp) {
		if (temp->key == k) {
			flag = true;
			break;
		}
		else if (temp->key > k) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (!flag) {
		cout << "Key not found" << endl;
		return;
	}
	if (!root->left && !root->right) {
		root = NULL;
		return;
	}
	struct node *parent = root, *ptr = root;
	flag = false;
	while (ptr->key != k) {
		parent = ptr;
		if (ptr->key > k) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	long long delete_choice;
	if (!ptr->left && !ptr->right) { // have no child
		delete_choice = 1;
	}
	else if (ptr->left && ptr->right) { // has 2 children
		delete_choice = 3;
	}
	else { // has 1 child
		delete_choice = 2;
	}
	if (delete_choice == 1) {
		if (parent->left == ptr) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}
	else if (delete_choice == 2) {
		if (parent == ptr) { // If we want to delete root.
			if (ptr->left == NULL) {
				parent = ptr->right;
				root = parent;
			}
			else {
				parent = ptr->left;
				root = parent;
			}
			return;
		}
		else {
			if (parent->left == ptr) {
				if (ptr->left == NULL) {
					parent->left = ptr->right;
				}
				else {
					parent->left = ptr->left;
				}
			}
			else {
				if (ptr->left == NULL) {
					parent->left = ptr->right;
				}
				else {
					parent->left = ptr->left;
				}
			}
			return;
		}
	}
	else {
		struct node *left_most = ptr->right;
		while (left_most->left) {
			left_most = left_most->left;
		}
		parent = ptr;
		long long info1 = left_most->key;
		delete_node(left_most->key);
		parent->key = info1;
	}
}

void search_node(long long k) {
	if (!root) {
		cout << "Tree is empty." << endl;
		return;
	}
	temp = root;
	bool flag = false;
	while (temp) {
		if (temp->key == k) {
			flag = true;
			break;
		}
		else if (temp->key > k) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (flag) {
		cout << k << " is present" << endl;
	}
	else {
		cout << k << " is not present" << endl;
	}
}

void inorder(struct node *root) {
	if (!root) {
		return;
	}
	inorder(root->left);
	cout << root->key << " ";
	inorder(root->right);
}

struct node *lca(struct node *root, struct node *p, struct node *q) {
	if (p->key < root->key && q->key < root->key) {
		return lca(root->left, p, q);
	}
	if (p->key > root->key && q->key > root->key) {
		return lca(root->right, p, q);
	}
	return root;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, x;
	cin >> N;
	root = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		if (!root) {
			NEW = new node(x);
			root = NEW;
			continue;
		}
		insert_node(root, x);
	}
	struct node *p = root->left->left;
	struct node *q = root->left->right;
	cout << "p: " << p->key << "   q: " << q->key << endl;

	// Method 1:
	// Iterative method to find lca. we check the current value and the other nodes' values. We know that left of a node is smaller and right of a node is greater than the node.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	temp = root;
	while (true) {
		if (p->key < temp->key && q->key < temp->key) {
			temp = temp->left;
		}
		else if (p->key > temp->key && q->key > temp->key) {
			temp = temp->right;
		}
		else {
			break;
		}
	}
	cout << temp->key << " is the Least Common Ancestor." << endl;

	// Method 2:
	// We will do the same thing but recursively.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	temp = lca(root, p, q);
	cout << temp->key << " is the Least Common Ancestor." << endl;
	return 0;
}