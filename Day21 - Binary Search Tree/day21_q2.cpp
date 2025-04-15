#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/kth-smallest-element-in-a-bst/

	Input:
	7 6
	7 3 9 5 1 11 13

	Output:
	11 is the 6th smallest element in the BST
	3 is the 6th largest element in the BST
	11 is the 6th smallest element in the BST
	3 is the 6th largest element in the BST
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

void kth_smallest(struct node *root, long long k, vector<long long> &v) {
	if (!root) {
		return;
	}
	kth_smallest(root->left, k, v);
	v.push_back(root->key);
	kth_smallest(root->right, k, v);
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

	// Method 1:
	// we will do inorder traversal and add the visited node to a vector and print the kth element in it.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	vector<long long> v;
	kth_smallest(root, k, v);
	cout << v[k - 1] << " is the " << k << "th smallest element in the BST" << endl;
	cout << v[N - k] << " is the " << k << "th largest element in the BST" << endl;

	// Method 2:
	// We will use Morris Traversal. In this traversal, we first create links to Inorder successor and print the data using this links, and finally revert the changes to restore original tree.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long cnt = 0; // count variable to keep count of visited Nodes
	long long k_small = LLONG_MIN;
	struct node *curr = root;
	while (curr) {
		if (!curr->left) {
			cnt++;
			if (cnt == k) {
				k_small = curr->key;
			}
			curr = curr->right;
		}
		else {
			// Find inorder predecessor of current Node
			struct node *pre = curr->left;
			while (pre->right && pre->right != curr) {
				pre = pre->right;
			}
			if (!pre->right) {
				// Set right child of predecessor to the current Node
				pre->right = curr;
				curr = curr->left;
			}
			// While breaking the links in so made temporary threaded tree we will check for the K smallest condition
			else {
				pre->right = NULL;
				cnt++;
				if (cnt == k) {
					k_small = curr->key;
				}
				curr = curr->right;
			}
		}
	}
	cout << k_small << " is the " << k << "th smallest element in the BST" << endl;
	cnt = 0;
	long long k_large = LLONG_MAX;
	curr = root;
	while (curr) {
		if (!curr->right) {
			cnt++;
			if (cnt == k) {
				k_large = curr->key;
			}
			curr = curr->left;
		}
		else {
			// Find inorder successor of current Node
			struct node *suc = curr->right;
			while (suc->left && suc->left != curr) {
				suc = suc->left;
			}
			if (!suc->left) {
				// Set left child of successor to the current Node
				suc->left = curr;
				curr = curr->right;
			}
			// Restoring the tree back to original binary search tree removing threaded links
			else {
				suc->left = NULL;
				cnt++;
				if (cnt == k) {
					k_large = curr->key;
				}
				curr = curr->left;
			}
		}
	}
	cout << k_large << " is the " << k << "th largest element in the BST" << endl;
	return 0;
}