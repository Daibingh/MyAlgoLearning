#include "utils.hpp"
using namespace std;

/*
给定一个非空二叉树，返回其最大路径和。

本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。
--------------------------------------------------------------------------------------
解法：

构造一个递归函数 maxPath(root) = 以 root 为根往下的路径的和的最大值 (一条腿的和)

路径的一般是   root
             /   \
则，该路径可以表示成 maxPath(root->left) + maxPath(root->right) + root->val
*/


class Solution {
    int res;
public:
    int maxPathSum(TreeNode* root) {
        res = INT_MIN;
        maxPath(root);
        return res;
    }

    // 递归求解一条腿的和的最大值
    int maxPath(TreeNode* root) {
        if (!root) return 0;
        int l = max(0, maxPath(root->left));
        int r = max(0, maxPath(root->right));
        int sum = l + r + root->val;  // 同时计算和更新总和的最大值 左腿 + 右腿 + 根
        res = max(res, sum);
        return root->val + max(l, r);  // 返回单侧的最大值
    }
    
};