#include "utils.hpp"
using namespace std;


/*
给定一个二叉树，检查它是否是镜像对称的。
-----------------------------------
解法：典型的递归，递归函数同时追踪两个树的位置
*/

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return !root || helper(root->left, root->right);
    }

    // 递归函数
    // 将 return 值 用逻辑公式表示出来
    bool helper(TreeNode* r1, TreeNode* r2) {
        return (!r1 && !r2)
            || ( ( r1 && r2 && r1->val == r2->val ) && helper(r1->left, r2->right) && helper(r1->right, r2->left) );
    }
};