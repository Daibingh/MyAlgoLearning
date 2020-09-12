#include "utils.hpp"
using namespace std;


/*

给定一棵二叉树，你需要计算它的直径长度。
一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
*/

// 递归函数的定义是返回单侧最大值
// 最优解不是靠返回，在递归函数内部更新
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        helper(root, res);
        return res;
    }

    int helper(TreeNode* root, int& res) {
        int left = root->left ? helper(root->left, res) + 1 : 0;
        int right = root->right ? helper(root->right, res) + 1 : 0;
        res = max(res, left + right);  // 最优解不是靠返回，在内部更新
        return max(left, right);  // 递归函数负责返回单边最大值
    }
};