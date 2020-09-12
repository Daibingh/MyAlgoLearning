#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;


/*
计算给定二叉树的所有左叶子之和。

示例：

    3
   / \
  9  20
    /  \
   15   7

在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24
-----------------------------------------------------
分析：
- 考察二叉树的遍历 dfs，分治
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;  // 遍历到底才返回
        int l_sum, r_sum;
        if (root->left && !root->left->left && !root->left->right) l_sum = root->left->val;  // 找到左叶子节点
        else l_sum =  sumOfLeftLeaves(root->left);  // 不是叶子节点，则往下遍历左子树
        r_sum = sumOfLeftLeaves(root->right);  // 遍历右子树
        return l_sum + r_sum;
    }
};


int main() {

}