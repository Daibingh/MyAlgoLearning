#include "utils.hpp"

using namespace std;

/*
在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

*/

// 动态规划，树的遍历，dp 表存 hash
class Solution {
    unordered_map<TreeNode*, int> mem;  // 用于存储 某个以root为根的子树的最优解
public:
    int rob(TreeNode* root) {
        if (!root) return 0;
        auto it = mem.find(root);
        if (it!=mem.end()) return mem[root];  // 先查表，没有再计算
        // 分类讨论两种情况 包含根、不包含根
        int res1 = root->val 
            + ( root->left == nullptr ? 0 :  ( rob(root->left->left) +  rob(root->left->right) ) )
            + ( root->right == nullptr ? 0 :  ( rob(root->right->left) +  rob(root->right->right) ) );
        int res2 = rob(root->left) + rob(root->right);
        return mem[root] = max(res1, res2);  // 取两种情况的最大值，填表
    }
};
