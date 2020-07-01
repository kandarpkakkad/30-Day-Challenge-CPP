#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

	Input:
	9
	1 2 3 7 6 5 4 8 9

	Output:
	p: 6
	q: 9
	2
	2
*/

struct node {
	long long key;
	struct node *left, *right;
	node (long long x) {
		key = x;
		left = right = NULL;
	}
} *root, *NEW, *temp;

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

struct node *lca(struct node *root, struct node *p, struct node *q) {
	if (!root || root == p || root == q) {
		return root;
	}
	struct node *l = lca(root->left, p, q);
	struct node *r = lca(root->right, p, q);
	if (l != NULL && r != NULL) {
		return root;
	}
	else if (l == NULL) {
		return r;
	}
	else {
		return l;
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
	struct node *p, *q;
	p = root->left->right;
	q = root->left->left->right;
	cout << "p: " << p->key << endl;
	cout << "q: " << q->key << endl;

	// Method 1:
	// For every node from root node we check that if two nodes have same parent we return it.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	struct node *ans = lca(root, p, q);
	cout << ans->key << endl;

	// Method 2:
	// Same process but we will not use recursion, but instead use a vector. We will use standard postorder traversal
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	temp = root;
	if (temp == p || temp == q) {
		cout << temp->key << endl;
	}
	vector<struct node *> pathp, pathq, temp1;
	temp1.push_back(temp);
	struct node *prev = NULL;
	while (pathp.empty() || pathq.empty()) {
		temp = temp1.back();
		if (temp == p) {
			pathp = temp1;
		}
		if (temp == q) {
			pathq = temp1;
		}
		if (!temp->left && ! temp->right || !temp->right && prev == temp->left || temp->right && prev == temp->right) {
			temp1.pop_back();
			prev = temp;
		}
		else {
			if (!temp->left || prev == temp->left) {
				temp1.push_back(temp->right);
			}
			else {
				temp1.push_back(temp->left);
			}
		}
	}
	long long n = min(pathp.size(), pathq.size());
	bool flag = false;
	for (long long i = 1; i < n; i++) {
		if (pathp[i] != pathq[i]) {
			flag = true;
			cout << pathp[i - 1]->key << endl;
			break;
		}
	}
	if (!flag) {
		cout << pathp[n - 1]->key << endl;
	}
	return 0;
}