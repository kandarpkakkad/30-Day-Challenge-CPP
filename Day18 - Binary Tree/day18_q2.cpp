#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/maximum-depth-of-binary-tree/

	Input:
	9
	1 2 3 7 6 5 4 8 9
	        1----------------1
	       / \
	      2   3--------------2
	     / \ / \
		7  6 5  4------------3
	   / \
	  8   9------------------4

	Output:
	4
	4
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
	return 1 + max(height(root->left), height(root->right));
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
	// Recursive method. We find the height of left and height subtree of each node and add it up.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	cout << height(root) << endl;

	// Method 2:
	// Iterative method. We traverse level order and at each level we increase the height.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	long long ans = 0;
	queue<struct node *> q;
	q.push(root);
	while (!q.empty()) {
		++ans;
		long long n = q.size();
		for (long long i = 0; i < n; i++) {
			temp = q.front();
			q.pop();
			if (temp->left) {
				q.push(temp->left);
			}
			if (temp->right) {
				q.push(temp->right);
			}
		}
	}
	cout << ans << endl;
	return 0;
}