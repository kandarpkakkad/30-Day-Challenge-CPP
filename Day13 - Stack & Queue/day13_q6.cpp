#include<bits/stdc++.h>

using namespace std;

/*
	https://leetcode.com/problems/valid-parentheses

	Input:
	()[]{}

	Output:
	Balanced
	Balanced

	Input:
	([{([{])}])

	Output:
	Not Balanced
	Not Balanced
*/

bool is_match(char c1, char c2) {
	if (c1 == '(' && c2 == ')') {
		return true;
	}
	if (c1 == '{' && c2 == '}') {
		return true;
	}
	if (c1 == '[' && c2 == ']') {
		return true;
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	freopen("../output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	long long N = s.length();

	// Method 1:
	// We insert opening parentheses in stack and remove it when closing appears. If stack is not empty at the end or for closing bracket there is no openinig bracket, parentheses are not balanced.
	// Time Complexity: O(n)
	// Space Complexity: O(n)
	stack<char> st;
	bool flag = true;
	for (long long i = 0; i < N; i++) {
		if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
			st.push(s[i]);
		}
		else if (s[i] == ')') {
			if (st.empty() || st.top() != '(') {
				flag = false;
				break;
			}
			else {
				st.pop();
			}
		}
		else if (s[i] == '}') {
			if (st.empty() || st.top() != '{') {
				flag = false;
				break;
			}
			else {
				st.pop();
			}
		}
		else if (s[i] == ']') {
			if (st.empty() || st.top() != '[') {
				flag = false;
				break;
			}
			else {
				st.pop();
			}
		}
	}
	if (!st.empty()) {
		flag = false;
	}
	if (flag) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}

	// Method 2:
	// We keep a pointer to see whether the the opposite parentheses exists or not. If the opposite parentheses exists we go in reverse order and check remaining opening parentheses.
	// Time Complexity: O(n)
	// Space Complexity: O(1)
	long long top = -1;
	for (long long i = 0; i < N; i++) {
		if (top < 0 || !is_match(s[top], s[i])) {
			top++;
			s[top] = s[i];
		}
		else {
			top--;
		}
	}
	if (top == -1) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}
	return 0;
}