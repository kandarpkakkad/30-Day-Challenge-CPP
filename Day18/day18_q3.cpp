#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/diameter-of-binary-tree/

	Input:
	9
	1 2 3 7 6 5 4 8 9
	        1
	       / \
	      2   3
	     / \ / \
		7  6 5  4
	   / \
	  8   9

	Output:
	5
	5
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

long long dfs(struct node *root, long long &diameter) {
	if (!root) {
		return 0;
	}
	long long leftdia = dfs(root->left, diameter);
	long long rightdia = dfs(root->right, diameter);
	if (diameter < leftdia + rightdia) {
		diameter = leftdia + rightdia;
	}
	return max(leftdia + 1, rightdia + 1);
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
	// DFS recursive method.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	long long ans = 0;
	dfs(root, ans);
	cout << ans << endl;

	// Method 2:
	// We will use postorder traversal technique to write the iterative solution.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	ans = 0;
	unordered_map<struct node *, long long> depths;
	stack<struct node *> st;
	st.push(root);
	while (!st.empty()) {
		temp = st.top();
		if (temp->left && depths.find(temp->left) == depths.end()) {
			st.push(temp->left);
		}
		else if (temp->right && depths.find(temp->right) == depths.end()) {
			st.push(temp->right);
		}
		else {
			st.pop();
			long long l = depths[temp->left], r = depths[temp->right];
			depths[temp] = max(l, r) + 1;
			ans = max(ans, l + r);
		}
	}
	cout << ans << endl;
	return 0;
}