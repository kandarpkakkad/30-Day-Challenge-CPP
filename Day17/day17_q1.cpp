#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/insertion-in-a-binary-tree-in-level-order/
	https://www.geeksforgeeks.org/deletion-binary-tree/

	Input:
	9
	i 7
	i 11
	i 10
	i 15
	d 7
	i 9
	i 8
	i 12
	d 9

	Output:
	7
	11 7
	11 7 10
	15 11 7 10
	11 15 10
	9 11 15 10
	9 11 8 15 10
	9 11 8 15 12 10
	12 11 8 15 10
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

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N;
	cin >> N;
	long long x;
	char choice;
	root = NULL;
	for (long long i = 0; i < N; i++) {
		cin >> choice;
		switch (choice) {
		case 'i':
			cin >> x;
			if (i == 0) {
				NEW = new node(x);
				root = NEW;
			}
			else {
				insert_node(root, x);
			}
			inorder(root);
			cout << endl;
			break;
		case 'd':
			cin >> x;
			delete_node(root, x);
			inorder(root);
			cout << endl;
			break;
		default:
			cout << "Invalid Choice" << endl;
			break;
		}
	}
	return 0;
}