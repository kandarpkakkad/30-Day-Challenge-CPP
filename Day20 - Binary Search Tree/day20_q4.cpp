#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

	Input:
	7
	4 2 5 3 1 6 7

	Output:
	No
	No
	No
	No

	Input:
	5
	4 2 5 1 3

	Output:
	Yes
	Yes
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

long long max_val(struct node *n) {
	if (!n) {
		return LLONG_MIN;
	}
	while (n) {
		if (n->right) {
			n = n->right;
		}
		else {
			break;
		}
	}
	return n->key;
}

long long min_val(struct node *n) {
	if (!n) {
		return LLONG_MAX;
	}
	while (n) {
		if (n->left) {
			n = n->left;
		}
		else {
			break;
		}
	}
	return n->key;
}

bool is_bst_1(struct node *root) {
	if (!root) {
		return true;
	}
	if (root->left && max_val(root->left) > root->key) {
		return false;
	}
	if (root->right && min_val(root->right) < root->key) {
		return false;
	}
	if (!is_bst_1(root->left) || !is_bst_1(root->right)) {
		return false;
	}
	return true;
}

bool is_bst_2(struct node *root, long long mn, long long mx) {
	if (!root) {
		return true;
	}
	if (root->key < mn || root->key > mx) {
		return false;
	}
	return (is_bst_2(root->left, mn, root->key - 1) && is_bst_2(root->right, root->key + 1, mx));
}

bool is_bst_3(struct node *root, struct node *l, struct node *r) {
	if (!root) {
		return true;
	}
	if ((l && root->key <= l->key) || (r && root->key >= r->key)) {
		return false;
	}
	return (is_bst_3(root->left, l, root) && is_bst_3(root->right, root, r));
}

bool is_bst_4(struct node *root, struct node *prev) {
	if (root) {
		if (!is_bst_4(root->left, prev)) {
			return false;
		}
		if (prev && root->key <= prev->key) {
			return false;
		}
		prev = root;
		return is_bst_4(root->right, prev);
	}
	return true;
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
	// For each node, check is the max value in left subtree is smaller than the node and min value in right subtree is greater than the node. This is not efficient solution as it traverses over some parts of tree many times.
	// Time Complexity: O(nlog(n))
	// Space Complexity: O(n) (recursive stack)
	if (is_bst_1(root)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// We will do the same method but will traverse each node only once. The trick is use a utility function.
	// Time Complexity: O(n)
	// Space Complexity; O(n) (recursive stack)
	if (is_bst_2(root, LLONG_MIN, LLONG_MAX)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 3:
	// We will do the same method but instead of min and max we will use left and right nodes.
	// Time Complexity: O(n)
	// Space Complexity; O(n) (recursive stack)
	if (is_bst_3(root, NULL, NULL)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 4:
	// We will do inorder traversal and keep track of previous node for checking values.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	if (is_bst_4(root, NULL)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}