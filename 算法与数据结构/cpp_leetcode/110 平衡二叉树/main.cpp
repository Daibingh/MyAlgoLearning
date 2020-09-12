#include <bits/stdc++.h>

using namespace std;

/*
给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
*/


class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return helper(root) != -1;
    }

    int helper(TreeNode* root) {
        if (!root) return 0;
        int left = helper(root->left);
        if (left==-1) return -1;
        int right = helper(root->right);
        if (right==-1) return -1;
        if (abs(left-right)<2) 
            return max(left, right)+1;
        else 
            return -1;
    }
};