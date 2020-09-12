#include "utils.hpp"
using namespace std;


/*

给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
返回:

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

// dfs search
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> path;
        helper(root, sum, res, path);
        return res;
    }

    void helper(TreeNode* root, int sum, vector<vector<int>>& res, vector<int>& path) {
        if (!root) return;
        sum -= root->val;
        path.push_back(root->val);
        if (!root->left && !root->right && sum==0) 
            res.push_back(path);
        helper(root->left, sum, res, path);
        helper(root->right, sum, res, path);
        path.pop_back();
    }
};