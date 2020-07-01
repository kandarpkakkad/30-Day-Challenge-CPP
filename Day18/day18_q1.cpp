#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/binary-tree-level-order-traversal/
	https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

	Input:
	7
	1 2 3 7 6 5 4

	Output:
	1
	2 3
	7 6 5 4

	1
	2 3
	4 5 6 7
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

	// Method 1 (Normal):
	// We just add the left first and right second to the queue for each node in the tree and then use the front of the queue to print level order traversal.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	queue<struct node *> q;
	q.push(root);
	while (!q.empty()) {
		long long size = q.size();
		while (size--) {
			temp = q.front();
			cout << temp->key << " ";
			q.pop();
			if (temp->left) {
				q.push(temp->left);
			}
			if (temp->right) {
				q.push(temp->right);
			}
		}
		cout << endl;
	}
	cout << endl;

	// Method 1 (Spiral):
	// Very similar approach to the above method but here we change the direction of printing and adding the the nodes i.e. whether right goes first or left goes first.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	deque<struct node *> d;
	d.push_back(root);
	long long dir = 0; // 0 = left, 1 = right.
	while (!d.empty()) {
		long long size = d.size();
		while (size--) {
			if (dir == 0) {
				temp = d.back();
				d.pop_back();
				if (temp->right) {
					d.push_front(temp->right);
				}
				if (temp->left) {
					d.push_front(temp->left);
				}
				cout << temp->key << " ";
			}
			else {
				temp = d.front();
				d.pop_front();
				if (temp->left) {
					d.push_back(temp->left);
				}
				if (temp->right) {
					d.push_back(temp->right);
				}
				cout << temp->key << " ";
			}
		}
		cout << endl;
		dir = 1 - dir;
	}
	return 0;
}