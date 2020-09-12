#include "utils.hpp"

using namespace std;

/*
给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回锯齿形层次遍历如下：

[
  [3],
  [20,9],
  [15,7]
]
-------------------------------------

- 层次遍历，记录每层个数

*/

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> res;
        queue<TreeNode*> q;
        q.push(root);
        bool f = true;
        while (!q.empty()) {
            int size = q.size();   // 记录该层节点个数
            vector<int> tmp(size);
            while (size--) {   // 遍历改层
                auto node = q.front();
                tmp[ f ? tmp.size()-size-1 : size ] = node->val;   // 对应位置赋值
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            res.push_back(tmp);
            f = !f;
        }
        
        return res;
    }
};