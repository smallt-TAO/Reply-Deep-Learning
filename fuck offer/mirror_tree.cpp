#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;

    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    void mirrorTree (struct TreeNode* root) {
        if (!root) {
            return;
        }

        swap(root -> left, root -> right);

        mirrorTree(root -> left);
        mirrorTree(root -> right);

    }

    void printThroughIn (struct TreeNode* root) {
        if (!root) {
            return;
        }

        cout << root -> val << " ";
        printThroughIn(root -> left);
        printThroughIn(root -> right);
    }

    void mirrorTree1 (struct TreeNode* root) {
        stack<TreeNode*> nodeStack;
        TreeNode* head = root;

        nodeStack.push(head);

        while (!nodeStack.empty()) {
            TreeNode* temp = nodeStack.top();
            nodeStack.pop();
            if (temp -> left || temp -> right) {
                swap(temp -> left, root -> right);
            }

            if (temp -> right != NULL) {
                nodeStack.push(temp -> right);
            }
            if (temp -> left != NULL) {
                nodeStack.push(temp -> left);
            }
        }

    }
};

int main() {
    TreeNode root(2);
    TreeNode node(3);
    TreeNode node1(4);
    root.left = &node;
    root.right = &node1;
    
    Solution solu;
    solu.printThroughIn(&root);
    cout << endl;
    solu.mirrorTree(&root);
    solu.printThroughIn(&root);
    cout << endl;
    solu.mirrorTree1(&root);
    solu.printThroughIn(&root);
    cout << endl;

    return 0;
}
    

