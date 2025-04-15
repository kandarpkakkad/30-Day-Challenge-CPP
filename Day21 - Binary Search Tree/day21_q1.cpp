#include<bits/stdc++.h>

using namespace std;

/*
	https://www.geeksforgeeks.org/floor-and-ceil-from-a-bst/

	Input:
	7 6
	7 3 9 5 1 11 13

	Output:
	7 is the ceil of 6
	5 is the floor of 6

	Input:
	7 14
	7 3 9 5 1 11 13

	Output:
	No Ceil
	13 is the floor of 14

	Input:
	7 -5
	7 3 9 5 1 11 13

	Output:
	1 is the ceil of -5
	No Floor
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

void inorder(struct node *root) {
	if (!root) {
		return;
	}
	inorder(root->left);
	cout << root->key << " ";
	inorder(root->right);
}

long long Ceil(struct node *root, long long input) {
	if (!root) {
		return LLONG_MIN;
	}
	if (root->key == input) {
		return root->key;
	}
	if (root->key < input) {
		return Ceil(root->right, input);
	}
	long long c = Ceil(root->left, input);
	return c >= input ? c : root->key;
}

long long Floor(struct node *root, long long input) {
	if (!root) {
		return LLONG_MAX;
	}
	if (root->key == input) {
		return root->key;
	}
	if (root->key > input) {
		return Floor(root->left, input);
	}
	long long f = Floor(root->right, input);
	return f <= input ? f : root->key;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	long long N, k, x;
	cin >> N >> k;
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

	// Method 1 (Ceil):
	// We will compare the input and value of each node. if we find a match we return it else we return the smallest number greater than input.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	if (Ceil(root, k) == LLONG_MIN) {
		cout << "No Ceil." << endl;
	}
	else {
		cout << Ceil(root, k) << " is the ceil of " << k << endl;
	}

	// Method 1 (Floor):
	// We will compare the input and value of each node. if we find a match we return it else we return the greatest number smaller than input.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	if (Floor(root, k) == LLONG_MAX) {
		cout << "No Floor" << endl;
	}
	else {
		cout << Floor(root, k) << " is the floor of " << k << endl;
	}
	return 0;
}