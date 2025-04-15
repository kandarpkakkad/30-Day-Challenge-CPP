#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/balanced-binary-tree/

	Input:
	7
	1 2 3 7 6 5 4

	        1
	       / \
	      2   3
	     / \
	    7  6
	   / \
	  5   4

	Output:
	No
	No
	No

	Input:
	7
	1 2 3 7 6 5 4 8 9

	        1
	       / \
	      2   3
	     / \ / \
	    7  6 8  9
	   / \
	  5   4

	Output:
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

long long height(struct node *root) {
	if (!root) {
		return 0;
	}
	return max(height(root->left), height(root->right)) + 1;
}

bool is_balanced(struct node *root) {
	if (!root) {
		return true;
	}
	return is_balanced(root->left) && is_balanced(root->right) && abs(height(root->left) - height(root->right)) <= 1;
}

long long height_2(struct node *root) {
	if (!root) {
		return -1;
	}
	long long left = height_2(root->left);
	long long right = height_2(root->right);
	if (left == LLONG_MAX || right == LLONG_MAX || abs(left - right) > 1) {
		return LLONG_MAX;
	}
	return 1 + max(left, right);
}

bool is_balanced_2(struct node *root) {
	if (!root) {
		return true;
	}
	return height_2(root) != LLONG_MAX;
}

bool is_balanced_3(struct node *root, long long &height) {
	long long lh = 0, rh = 0;
	long long l = 0, r = 0;
	if (!root) {
		height = 0;
		return 1;
	}
	l = is_balanced_3(root->left, lh);
	r = is_balanced_3(root->right, rh);
	height = max(lh, rh) + 1;
	if (abs(lh - rh) >= 2) {
		return false;
	}
	else {
		return l && r;
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
	cin >> x;
	root = new node(x);
	cin >> x;
	root->left = new node(x);
	cin >> x;
	root->right = new node(x);
	cin >> x;
	root->left->left = new node(x);
	cin >> x;
	root->left->right = new node(x);
	cin >> x;
	root->left->left->left = new node(x);
	cin >> x;
	root->left->left->right = new node(x);
	cin >> x;
	root->right->left = new node(x);
	cin >> x;
	root->right->right = new node(x);

	// Method 1:
	// We find height of each subtree and and check if the subtrees are balanced or not. We do it recursively.
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2) (recursive stack)
	if (is_balanced(root)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 2:
	// We will use the same method but we won't calculate height of every subtrees more than 1 one time.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	if (is_balanced_2(root)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	// Method 3:
	// Same approach as above but instead of 2 functions we use one.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	long long height = 0;
	if (is_balanced_3(root, height)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}