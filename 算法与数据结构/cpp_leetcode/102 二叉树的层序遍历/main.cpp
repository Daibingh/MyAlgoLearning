#include "utils.hpp"
using namespace std;

/*
给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

 

示例：
二叉树：[3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [9,20],
  [15,7]
]
----------------------------------
二叉树层序遍历，记录每层个数

*/


class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        if (root) q.push(root);
        vector<vector<int>> res;
        while (!q.empty()) {
            vector<int> tmp;
            int size = q.size();  // 获取上一层个数
            for (int i=0;i<size;++i) {  // 区分每一层
                TreeNode* node = q.front();
                tmp.push_back(node->val);
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(tmp);
        }
        return res;
    }
};