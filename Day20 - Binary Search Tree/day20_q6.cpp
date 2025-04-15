#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/inorder-successor-in-bst/

	Input:
	7 5
	4 2 5 3 1 6 7

	Output:
	Predecessor: 4   Successor: 6
	Predecessor: 4   Successor: 6
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

void pre_suc(struct node *root, struct node *&pre, struct node *&suc, long long k) {
	if (!root) {
		return;
	}
	if (root->key == k) {
		if (root->left) {
			temp = root->left;
			while (temp->right) {
				temp = temp->right;
			}
			pre = temp;
		}
		if (root->right) {
			temp = root->right;
			while (temp->left) {
				temp = temp->left;
			}
			suc = temp;
		}
		return;
	}
	if (root->key > k) {
		suc = root;
		pre_suc(root->left, pre, suc, k);
	}
	else {
		pre = root;
		pre_suc(root->right, pre, suc, k);
	}
}

void pre_suc_2(struct node *root, struct node *&p, struct node *&q, long long k) {
	if (!root) {
		return;
	}
	pre_suc_2(root->left, p, q, k);
	if (root && root->key > k) {
		if ((!q) || (q) && q->key > root->key) {
			q = root;
		}
	}
	else if (root && root->key < k) {
		p = root;
	}
	pre_suc_2(root->right, p, q, k);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k, x;
	cin >> N >> k;
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
	struct node *pre = NULL, *suc = NULL;

	// Method 1:
	// The idea is simple. We store the parent node of each node just in case successor or predecessor does not exist.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	pre_suc(root, pre, suc, k);
	if (!pre && !suc) {
		cout << "None None" << endl;
	}
	else if (!pre) {
		cout << "Successor: " << suc->key << endl;
	}
	else if (!suc) {
		cout << "Predecessor: " << pre->key << endl;
	}
	else {
		cout << "Predecessor: " << pre->key << "   Successor: " << suc->key << endl;
	}

	// Method 2:
	// We do inorder traversal and check if current node is smaller than the given key. If greater check if smaller than successor and update it.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	pre = NULL, suc = NULL;
	pre_suc_2(root, pre, suc, k);
	if (!pre && !suc) {
		cout << "None None" << endl;
	}
	else if (!pre) {
		cout << "Successor: " << suc->key << endl;
	}
	else if (!suc) {
		cout << "Predecessor: " << pre->key << endl;
	}
	else {
		cout << "Predecessor: " << pre->key << "   Successor: " << suc->key << endl;
	}
	return 0;
}