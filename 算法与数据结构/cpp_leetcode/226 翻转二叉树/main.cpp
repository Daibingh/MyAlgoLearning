#include "utils.hpp"

using namespace std;

/*
翻转一棵二叉树。
*/


class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        invertTree(root->left);  // 递归翻转左侧
        invertTree(root->right);  // 递归翻转右侧
        TreeNode* tmp = root->left;  // 交换左右两侧
        root->left = root->right;
        root->right = tmp;
        return root;
    }
};