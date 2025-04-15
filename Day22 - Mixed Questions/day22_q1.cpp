#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/

	You need to run all the methods separately

	Input:
	7
	4 2 6 3 1 5 7

	Output:
	3 2 1 4 5 6 7
	3 2 1 4 5 6 7
	3 2 1 4 5 6 7
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

struct node *bt_2_dll_1(struct node *root) {
	if (!root) {
		return root;
	}
	if (root->left) {
		struct node *left = bt_2_dll_1(root->left);
		while (left->right) {
			left = left->right;
		}
		left->right = root;
		root->left = left;
	}
	if (root->right) {
		struct node *right = bt_2_dll_1(root->right);
		while (right->left) {
			right = right->left;
		}
		right->left = root;
		root->right = right;
	}
	return root;
}

void fix_pre_ptr(struct node *root) {
	static struct node *pre = NULL;
	if (root) {
		fix_pre_ptr(root->left);
		root->left = pre;
		pre = root;
		fix_pre_ptr(root->right);
	}
}

struct node *fix_next_ptr(struct node *root) {
	struct node *pre = NULL;
	while (root && root->right) {
		root = root->right;
	}
	while (root && root->left) {
		pre = root;
		root = root->left;
		root->right = pre;
	}
	return root;
}

struct node *bt_2_dll_2(struct node *root) {
	fix_pre_ptr(root);
	return fix_next_ptr(root);
}

void bt_2_dll_3(struct node *root, struct node *&head) {
	if (!root) {
		return;
	}
	static node *pre = NULL;
	bt_2_dll_3(root->left, head);
	if (!pre) {
		head = root;
	}
	else {
		root->left = pre;
		pre->right = root;
	}
	pre = root;
	bt_2_dll_3(root->right, head);
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

	// Method 1:
	// If left subtree exists, process the left subtree
	// 		1.a) Recursively convert the left subtree to DLL.
	// 		1.b) Then find inorder predecessor of root in left subtree (inorder predecessor is rightmost node in left subtree).
	// 		1.c) Make inorder predecessor as previous of root and root as next of inorder predecessor.
	// 2. If right subtree exists, process the right subtree (Below 3 steps are similar to left subtree).
	// 		2.a) Recursively convert the right subtree to DLL.
	// 		2.b) Then find inorder successor of root in right subtree (inorder successor is leftmost node in right subtree).
	// 		2.c) Make inorder successor as next of root and root as previous of inorder successor.
	// 3. Find the leftmost node and return it (the leftmost node is always head of converted DLL).
	// Time Complexity: O(n^2)
	// Space Complexity: O(n^2) (recursive stack)
	root = bt_2_dll_1(root);
	// Make root the head of the linked list.
	while (root->left) {
		root = root->left;
	}
	temp = root;
	while (temp) {
		cout << temp->key << " ";
		temp = temp->right;
	}

	// Method 2:
	// 1) Fix Left Pointers: In this step, we change left pointers to point to previous nodes in DLL. The idea is simple, we do inorder traversal of tree. In inorder traversal, we keep track of previous visited node and change left pointer to the previous node. See fixPrevPtr() in below implementation.
	// 2) Fix Right Pointers: The above is intuitive and simple. How to change right pointers to point to next node in DLL? The idea is to use left pointers fixed in step 1. We start from the rightmost node in Binary Tree (BT). The rightmost node is the last node in DLL. Since left pointers are changed to point to previous node in DLL, we can linearly traverse the complete DLL using these pointers. The traversal would be from last to first node. While traversing the DLL, we keep track of the previously visited node and change the right pointer to the previous node. See fixNextPtr() in below implementation.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	root = bt_2_dll_2(root);
	temp = root;
	while (temp) {
		cout << temp->key << " ";
		temp = temp->right;
	}

	// Method 3:
	// The idea is to do inorder traversal of the binary tree. While doing inorder traversal, keep track of the previously visited node in a variable say prev. For every visited node, make it next of prev and previous of this node as prev.
	// Time Complexity: O(n)
	// Space Complexity: O(n) (recursive stack)
	struct node *head = NULL;
	bt_2_dll_3(root, head);
	temp = head;
	while (temp) {
		cout << temp->key << " ";
		temp = temp->right;
	}
	return 0;
}