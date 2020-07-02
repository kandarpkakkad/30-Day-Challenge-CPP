#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

	Input:
	5
	9 3 15 20 7
	9 15 7 20 3

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

struct node *build_tree(long long post_start, long long ino_start, long long ino_end, vector<long long> &ino, vector<long long> &post) {
	if (post_start < 0 || ino_start > ino_end) {
		return NULL;
	}
	struct node *root = new node(post[post_start]);
	long long ino_id = 0;
	for (long long i = ino_start; i <= ino_end; i++) {
		if (ino[i] == post[post_start]) {
			ino_id = i;
			break;
		}
	}
	root->left = build_tree(post_start - (ino_end - ino_id) - 1, ino_start, ino_id - 1, ino, post);
	root->right = build_tree(post_start - 1, ino_id + 1, ino_end, ino, post);
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
	vector<long long> post, ino;
	for (long long i = 0; i < N; i++) {
		cin >> x;
		ino.push_back(x);
	}
	for (long long i = 0; i < N; i++) {
		cin >> x;
		post.push_back(x);
	}

	// Method 1:
	// Iterative method where we store the next nodes in stack to reserve the position of the nodes.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	struct node *curr = NULL;
	long long i = 0, j = 0;
	stack<struct node *> st;
	while (i < ino.size() && j < post.size()) {
		if (ino[i] == post[j]) {
			temp = new node(ino[i]);
			temp->left = curr;
			curr = temp;
			i++;
			j++;
		}
		else {
			if (!st.empty() && post[j] == st.top()->key) {
				temp = st.top();
				st.pop();
				temp->right = curr;
				curr = temp;
				j++;
			}
			else {
				temp = new node(ino[i]);
				temp->left = curr;
				curr = NULL;
				st.push(temp);
				i++;
			}
		}
	}
	while (!st.empty()) {
		temp = st.top();
		st.pop();
		temp->right = curr;
		curr = temp;
	}
	root = curr;
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
	// We will do the same thing as above but with recursion.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	root = build_tree(post.size() - 1, 0, ino.size() - 1, ino, post);
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