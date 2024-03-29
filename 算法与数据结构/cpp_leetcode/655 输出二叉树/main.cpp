#include "utils.hpp"
#include <bits/stdc++.h>

using namespace std;

/*
在一个 m*n 的二维字符串数组中输出二叉树，并遵守以下规则：

行数 m 应当等于给定二叉树的高度。
列数 n 应当总是奇数。
根节点的值（以字符串格式给出）应当放在可放置的第一行正中间。根节点所在的行与列会将剩余空间划分为两部分（左下部分和右下部分）。你应该将左子树输出在左下部分，右子树输出在右下部分。左下和右下部分应当有相同的大小。即使一个子树为空而另一个非空，你不需要为空的子树输出任何东西，但仍需要为另一个子树留出足够的空间。然而，如果两个子树都为空则不需要为它们留出任何空间。
每个未使用的空间应包含一个空的字符串""。
使用相同的规则输出子树。
示例 1:

输入:
     1
    /
   2
输出:
[["", "1", ""],
 ["2", "", ""]]
-------------------------------
分析：
- 分治，二分思想


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
    vector<vector<string>> printTree(TreeNode* root) {

        int h = getHeight(root);
        int w = (1<<h)-1;  // 2*h-1
        vector<vector<string>> res(h, vector<string>(w, ""));
        fill(root, res, 0, 0, w-1);
        return res;
    }
    
    void fill(TreeNode* root, vector<vector<string>>& res, int h, int l, int r) {
        if (!root) return;
        int mid = (l + r) / 2;
        res[h][mid] = std::to_string(root->val);
        fill(root->left, res, h+1, l, mid-1);
        fill(root->right, res, h+1, mid+1, r);
    }
    
    // 求二叉树的高度
    int getHeight(TreeNode* root) {
        if (!root) return 0;
        return std::max(getHeight(root->left), getHeight(root->right))+1;
    }
};

int main()
{
    
}