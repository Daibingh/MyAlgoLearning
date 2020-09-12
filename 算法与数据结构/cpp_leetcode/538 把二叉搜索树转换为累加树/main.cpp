#include "utils.hpp"
using namespace std;

/*
给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节点值之和。

 

例如：

输入: 原始二叉搜索树:
              5
            /   \
           2     13

输出: 转换为累加树:
             18
            /   \
          20     13
*/


// 中序遍历的反向遍历，同时累加和
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        helper(root, sum);
        return root;
    }

    void helper(TreeNode* root, int& sum) {  // 这里是引用，因为它是全局修改的，不需要回溯
        if (root) {
            helper(root->right, sum);
            sum += root->val;
            root->val = sum;
            helper(root->left, sum);
        }
    }
};