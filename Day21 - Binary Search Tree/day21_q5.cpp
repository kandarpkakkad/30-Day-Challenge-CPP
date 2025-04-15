#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/largest-bst-subtree/

	Input:
	7
	4 2 5 3 1 6 7

	Output:
	Size of largest BST in Binary Tree is: 7
	Size of largest BST in Binary Tree is: 1

	Input:
	7
	4 2 6 3 1 5 7

	Output:
	Size of largest BST in Binary Tree is: 7
	Size of largest BST in Binary Tree is: 3
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

void inorder(struct node *root) {
	if (!root) {
		return;
	}
	inorder(root->left);
	cout << root->key << " ";
	inorder(root->right);
}

bool is_bst(struct node *root) {
	struct node *prev = NULL;
	if (root) {
		if (!is_bst(root->left)) {
			return false;
		}
		if (prev && root->key <= prev->key) {
			return false;
		}
		prev = root;
		return is_bst(root->right);
	}
	return true;
}

long long size(struct node *root) {
	if (!root) {
		return 0;
	}
	return size(root->left) + 1 + size(root->right);
}

long long largest_bst(struct node *root) {
	if (is_bst(root)) {
		return size(root);
	}
	return max(largest_bst(root->left), largest_bst(root->right));
}

long long largest_bst_2(struct node *root, long long &min_ref, long long &max_ref, long long &max_size_ref, bool &is_bst_ref) {
	if (!root) {
		is_bst_ref = true;
		return 0;
	}
	long long mn = LLONG_MAX;
	bool left_flag = false;
	bool right_flag = false;
	long long lhs, rhs;
	max_ref = LLONG_MIN;
	lhs = largest_bst_2(root->left, min_ref, max_ref, max_size_ref, is_bst_ref);
	if (is_bst_ref && root->key > max_ref) {
		left_flag = true;
	}
	mn = min_ref;
	min_ref = LLONG_MAX;
	rhs = largest_bst_2(root->right, min_ref, max_ref, max_size_ref, is_bst_ref);
	if (is_bst_ref && root->key < min_ref) {
		right_flag = true;
	}
	if (mn < min_ref) {
		min_ref = mn;
	}
	if (root->key < min_ref) {
		min_ref = root->key;
	}
	if (root->key > max_ref) {
		max_ref = root->key;
	}
	if (left_flag && right_flag) {
		if (lhs + 1 + rhs > max_size_ref) {
			max_size_ref = lhs + 1 + rhs;
		}
		return lhs + 1 + rhs;
	}
	else {
		is_bst_ref = false;
		return 0;
	}
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

	// Method 1:
	// Start from root and do an inorder traversal of the tree. For each node N, check whether the subtree rooted with N is BST or not. If BST, then return size of the subtree rooted with N. Else, recur down the left and right subtrees and return the maximum of values returned by left and right subtrees. This method is simple but inefficient. You can see in the example.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n) (recursive stack)
	cout << "Size of largest BST in Binary Tree is: " << largest_bst(root) << endl;

	// Method 2:
	// In method 1, we traverse the tree in top down manner and do BST test for every node. If we traverse the tree in bottom up manner, then we can pass information about subtrees to the parent. The subtrees need to pass the following information up the tree for the finding the largest BST.
	// 1) Whether the subtree itself is BST or not
	// 2) If the subtree is left subtree of its parent, then maximum value in it. And if it is right subtree then minimum value in it.
	// 3) Size of this subtree if this subtree is BST
	long long mn = LLONG_MAX;
	long long mx = LLONG_MIN;
	long long max_size = 0;
	bool is_bst_ref = false;
	largest_bst_2(root, mn, mx, max_size, is_bst_ref);
	cout << "Size of largest BST in Binary Tree is: " << max_size << endl;
	return 0;
}