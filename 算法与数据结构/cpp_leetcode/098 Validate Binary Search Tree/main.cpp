#include "utils.hpp"
using namespace std;

/*
验证 BST 的合法性
注意：BST 的理解误区
要求 左子树 都比根 小，右子树 都比根 大，并非仅只相邻的父子大小关系！！！
----------------
解法：
- 1. 递归 O(n)，追踪上下界
- 2. 中序遍历递增
*/

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MAX, LONG_MIN);
    }

    // 边界用 long long
    bool helper(TreeNode* root, long long upper, long long lower) {
        if (!root) return true;
        return root->val > lower 
            && root->val < upper 
            && helper(root->left, root->val, lower) 
            && helper(root->right, upper, root->val);
    }
};