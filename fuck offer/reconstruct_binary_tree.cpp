#include <iostream>
#include <vector>

using namespace std;
// #define __tmain main

#ifdef __tmain
#define debug cout
#else
#define debug 0 && cout
#endif


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x): 
    val(x), left(NULL), right(NULL) {}

    static void PreOrder(TreeNode* root) {
        if (root) {
            cout << root->val << " ";
            PreOrder(root->left);
            PreOrder(root->right);
        } else {
            return;
        }
    }

    static void InOrder(TreeNode* root) {
        if (root) {
            InOrder(root->left);
            cout << root->val << " ";
            InOrder(root->right);
        }
        return ;
    }

};


class Solution {
public:
    struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) {
        if (pre.size() != in.size()) {
            cout << "ERROR: length of vector is not equation" << endl;
        }

        if (pre.size() == 0 && in.size() == 0) {
            return NULL;
        }
        
        debug << pre[0] << endl;

        TreeNode* root = new TreeNode(pre[0]);
        int rootIndex = 0;
        for (int i = 0; i < in.size(); ++i) {
            if (in[i] == pre[0]) {
                rootIndex = i;
                break;
            }
        }

        vector<int> preLeft(rootIndex), inLeft(rootIndex);
        vector<int> preRight(in.size() - rootIndex - 1);
        vector<int> inRight(in.size() - rootIndex - 1);
        for (int i = 0; i < pre.size(); ++i) {
            if (i < rootIndex) {
                preLeft[i] = pre[i + 1];
                inLeft[i] = in[i];
                debug << "*" << preLeft[i] << " " << inLeft[i] << " ";
            }
            debug << endl;

            if (i > rootIndex) {
                preRight[i - rootIndex - 1] = pre[i];
                inRight[i - rootIndex - 1] = in[i];
            }
        }
        
        for (auto a : preLeft) {
            debug << a << " ";
        }
        debug << endl;

        root->left = reConstructBinaryTree(preLeft, inLeft);
        root->right = reConstructBinaryTree(preRight, inRight);

        return root;
    }
};

int main() {
    int pre[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
    int in[] = { 4, 7, 2, 1, 5, 3, 8, 6 };

    vector<int> preOrder(pre, pre + 8);
    vector<int> inOrder(in, in + 8);

    Solution solu;
    TreeNode* root = solu.reConstructBinaryTree(preOrder, inOrder);

    cout << "pre order" << endl;
    TreeNode::PreOrder(root);
    cout << endl;

    cout << "In order" << endl;
    TreeNode::InOrder(root);
    cout << endl;

}

