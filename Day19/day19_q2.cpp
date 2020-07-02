#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

	Input:
	5
	3 9 20 15 7 // Preorder
	9 3 15 20 7 // Inorder

	Output:
	Preorder:
	3 9 20 15 7
	Inorder:
	9 3 15 20 7
	Postorder:
	7 15 20 9 3

	Preorder:
	3 9 20 15 7
	Inorder:
	9 3 15 20 7
	Postorder:
	7 15 20 9 3
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

void preorder(struct node *root) {
	if (!root) {
		return;
	}
	cout << root->key << " ";
	preorder(root->left);
	preorder(root->right);
}

void inorder(struct node *root) {
	if (!root) {
		return;
	}
	inorder(root->left);
	cout << root->key << " ";
	inorder(root->right);
}

void postorder(struct node *root) {
	if (!root) {
		return;
	}
	postorder(root->right);
	postorder(root->left);
	cout << root->key << " ";
}

struct node * build_tree(vector<long long> pre, vector<long long> ino) {
	if (pre.size() == 0) {
		return NULL;
	}
	struct node *root = new node(pre[0]);
	long long i = find(ino.begin(), ino.end(), pre[0]) - ino.begin();
	vector<long long> ino_left(ino.begin(), ino.begin() + i);
	vector<long long> ino_right(ino.begin() + i + 1, ino.end());
	vector<long long> pre_left(pre.begin() + 1, pre.begin() + i + 1);
	vector<long long> pre_right(pre.begin() + i + 1, pre.end());
	root->left = build_tree(pre_left, ino_left);
	root->right = build_tree(pre_right, ino_right);
	return root;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	vector<long long> pre;
	vector<long long> ino;
	long long x;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		pre.push_back(x);
	}
	for (long long i = 0; i < N; i++) {
		cin >> x;
		ino.push_back(x);
	}

	// Method 1:
	// Iterative method to store preorder in stack and compare it with inorder to make a tree.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	long long j = 0;
	root = new node(pre[0]);
	stack<struct node *> st;
	st.push(root);
	temp = NULL;
	for (long long i = 1; i < N; i++) {
		struct node *curr = new node(pre[i]);
		while (st.size() > 0 && st.top()->key == ino[j]) {
			temp = st.top();
			st.pop();
			j++;
		}
		if (temp != NULL) {
			temp->right = curr;
			temp = NULL;
		}
		else {
			st.top()->left = curr;
		}
		st.push(curr);
	}
	cout << "Preorder:" << endl;
	preorder(root);
	cout << endl;
	cout << "Inorder:" << endl;
	inorder(root);
	cout << endl;
	cout << "Postorder:" << endl;
	postorder(root);
	cout << endl << endl;

	// Method 2:
	// We will build tree by dividing it into left and right subtrees and assigning it at right position.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	root = build_tree(pre, ino);
	cout << "Preorder:" << endl;
	preorder(root);
	cout << endl;
	cout << "Inorder:" << endl;
	inorder(root);
	cout << endl;
	cout << "Postorder:" << endl;
	postorder(root);
	cout << endl;
	return 0;
}