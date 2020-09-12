#include "utils.hpp"
using namespace std;

/*
给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。

说明：
你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。
*/

// 中序遍历 全局引用变量计数
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int res  = 0;
        helper(root, k, res);
        return res;
    }

    void helper(TreeNode* root, int & k, int & res) {
        if (!root || k==0) return;  // 找到之后 k=0，避免继续遍历
        helper(root->left, k, res);
        if (--k==0) {
            res = root->val;
            return;
        }
        helper(root->right, k, res);
    }
};