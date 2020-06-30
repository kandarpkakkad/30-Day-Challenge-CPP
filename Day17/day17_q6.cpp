#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/bottom-view-binary-tree/

	Input:
	10
	7 11 10 15 9 8 12 17 21 24

	Output:
	10 15 12 24 17 8
	15 10 12 24 17 8
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

void print_botton_recursive(struct node *root, long long dist, long long level, unordered_map<long long, pair<long long, long long>> &um) {
	if (!root) {
		return;
	}
	if (level >= um[dist].second) {
		um[dist] = make_pair(root->key, level);
	}
	print_botton_recursive(root->left, dist - 1, level + 1, um);
	print_botton_recursive(root->right, dist + 1, level + 1, um);
}

void bottom_view_recursive(struct node *root) {
	unordered_map<long long, pair<long long, long long>> um;
	print_botton_recursive(root, 0, 0, um);
	for (auto it : um) {
		cout << it.second.first << " ";
	}
	cout << endl;
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
	// Recursive method to find bottom view. We create instance of each visible layer from bottom in an array and print them.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	bottom_view_recursive(root);

	// Method 2:
	// Iterative method does the same but instead of using inbuilt recursion stack we will use queue.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	temp = NULL;
	unordered_map<long long, long long> um;
	queue<pair<struct node *, long long>> q;
	q.push({root, 0});
	while (!q.empty()) {
		long long size = q.size();
		while (size--) {
			temp = q.front().first;
			long long level = q.front().second;
			q.pop();
			um[level] = temp->key;
			if (temp->left) {
				q.push({temp->left, level - 1});
			}
			if (temp->right) {
				q.push({temp->right, level + 1});
			}
		}
	}
	for (auto it : um) {
		cout << it.second << " ";
	}
	cout << endl;
	return 0;
}