#include <bits/stdc++.h>

using namespace std;

/*
给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 
输入数据保证，新值和原始二叉搜索树中的任意节点值都不同。
注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回任意有效的结果。
*/

// 递归
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (val > root->val) {
            root->right = insertIntoBST(root->right, val);
        }
        else {
            root->left = insertIntoBST(root->left, val);
        }
        return root;
    }
};