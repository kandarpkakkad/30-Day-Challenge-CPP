#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

	9223372036854775807 = null = $

	Input:
	7
	4 2 6 9223372036854775807 9223372036854775807 5 7

	Output:
	4,2,6,$,$,5,7,
	2 4 5 6 7
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

	// Method 1 (Serialize):
	// We will do level order traversing and make an output sting.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	queue<struct node *> q;
	q.push(root);
	string str;
	while (!q.empty()) {
		if (!q.front()) {
			str += "$,";
		}
		else {
			if (q.front()->left || q.front()->right) {
				q.push(q.front()->left);
				q.push(q.front()->right);
			}
			if (q.front()->key == LLONG_MAX) {
				str += "$,";
			}
			else {
				str += to_string(q.front()->key) + ",";
			}
		}
		q.pop();
	}
	cout << str << endl;

	// Method 1 (Deserialize):
	// We will create new nodes and insert them to new root while skipping the $ i.e. null.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	// NOTE: Here str i.e. the output of serialization is the input.
	struct node *root2 = NULL;
	queue<struct node **> q2;
	q2.push(&root2);
	string::iterator first = str.begin();
	while (first != str.end()) {
		struct node **temp2 = q2.front();
		if (*first == '$') {
			advance(first, 2);
		}
		else {
			string::iterator last = find(first, str.end(), ',');
			long long val = stoi(string(first, last));
			*temp2 = new node(val);
			q2.push(&((*temp2)->left));
			q2.push(&((*temp2)->right));
			first = next(last);
		}
		q2.pop();
	}
	inorder(root2);
	cout << endl;
	return 0;
}