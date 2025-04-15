#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/binary-search-tree-iterator/

	Input:
	7
	4 2 5 3 1 6 7

	Output:
	1 2 3 4 5 6 7
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
	NEW = new node(k);
	temp = root;
	while (temp) {
		if (k > temp->key) {
			if (temp->right) {
				temp = temp->right;
			}
			else {
				temp->right = NEW;
				return;
			}
		}
		else {
			if (temp->left) {
				temp = temp->left;
			}
			else {
				temp->left = NEW;
				return;
			}
		}
	}
}

void delete_node(long long k) {
	if (!root) {
		return;
	}
	temp = root;
	bool flag = false;
	while (temp) {
		if (temp->key == k) {
			flag = true;
			break;
		}
		else if (temp->key > k) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (!flag) {
		cout << "Key not found" << endl;
		return;
	}
	if (!root->left && !root->right) {
		root = NULL;
		return;
	}
	struct node *parent = root, *ptr = root;
	flag = false;
	while (ptr->key != k) {
		parent = ptr;
		if (ptr->key > k) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	long long delete_choice;
	if (!ptr->left && !ptr->right) { // have no child
		delete_choice = 1;
	}
	else if (ptr->left && ptr->right) { // has 2 children
		delete_choice = 3;
	}
	else { // has 1 child
		delete_choice = 2;
	}
	if (delete_choice == 1) {
		if (parent->left == ptr) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}
	else if (delete_choice == 2) {
		if (parent == ptr) { // If we want to delete root.
			if (ptr->left == NULL) {
				parent = ptr->right;
				root = parent;
			}
			else {
				parent = ptr->left;
				root = parent;
			}
			return;
		}
		else {
			if (parent->left == ptr) {
				if (ptr->left == NULL) {
					parent->left = ptr->right;
				}
				else {
					parent->left = ptr->left;
				}
			}
			else {
				if (ptr->left == NULL) {
					parent->left = ptr->right;
				}
				else {
					parent->left = ptr->left;
				}
			}
			return;
		}
	}
	else {
		struct node *left_most = ptr->right;
		while (left_most->left) {
			left_most = left_most->left;
		}
		parent = ptr;
		long long info1 = left_most->key;
		delete_node(left_most->key);
		parent->key = info1;
	}
}

void search_node(long long k) {
	if (!root) {
		cout << "Tree is empty." << endl;
		return;
	}
	temp = root;
	bool flag = false;
	while (temp) {
		if (temp->key == k) {
			flag = true;
			break;
		}
		else if (temp->key > k) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (flag) {
		cout << k << " is present" << endl;
	}
	else {
		cout << k << " is not present" << endl;
	}
}

class bst_iterator {
private:
	stack<struct node *> st;
public:
	void find_left(struct node *root) {
		struct node *t = root;
		while (t) {
			st.push(t);
			t = t->left;
		}
	}

	bst_iterator(struct node *root) {
		find_left(root);
	}

	bool has_next() {
		return !st.empty();
	}

	long long next() {
		struct node *top = st.top();
		st.pop();
		if (top->right) {
			find_left(top->right);
		}
		return top->key;
	}
};

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

	bst_iterator *it = new bst_iterator(root);
	while (it->has_next()) {
		cout << it->next() << " ";
	}
	cout << endl;
	return 0;
}