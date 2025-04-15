#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

	Run the methods one by one.

	Input:
	7
	1 2 5 3 4 6 7
	      1
	     / \
	    2   5
	   / \ / \
	  3  4 6  7

	Output:
	1 2 3 4 5 6 7
	1 2 3 4 5 6 7
	1
	 \
	  2
	   \
	    3
	     \
	      4
	       \
	        5
	         \
	          6
	           \
	            7
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

void flatten(struct node *root3) {
	if (!root3) {
		return;
	}
	flatten(root3->left);
	flatten(root3->right);
	struct node *temp = root3->right;
	root3->right = root3->left;
	root3->left = NULL;
	while (root3->right) {
		root3 = root3->right;
	}
	root3->right = temp;
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
	// We change the links of the tree to make it linked list.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	struct node *root2 = root;
	while (root2) {
		if (root2->left && root2->right) {
			temp = root2->left;
			while (temp->right) {
				temp = temp->right;
			}
			temp->right = root2->right;
			root2->right = root2->left;
			root2->left = NULL;
		}
		root2 = root2->right;
	}
	temp = root;
	while (temp) {
		cout << temp->key << " ";
		temp = temp->right;
	}
	cout << endl;

	// Method 2:
	// We start from last of left subtree and chaage the links recursively.
	// Time Compelxity: O(n)
	// Space Complexity: O(n) (recursive stack)
	struct node *root3 = root;
	flatten(root3);
	temp = root;
	while (temp) {
		cout << temp->key << " ";
		temp = temp->right;
	}
	return 0;
}