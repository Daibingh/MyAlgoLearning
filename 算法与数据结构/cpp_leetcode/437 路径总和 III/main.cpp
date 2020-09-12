#include "utils.hpp"
using namespace std;

/*
给定一个二叉树，它的每个结点都存放着一个整数值。

找出路径和等于给定数值的路径总数。

路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

示例：

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

返回 3。和等于 8 的路径有:

1.  5 -> 3
2.  5 -> 2 -> 1
3.  -3 -> 11

*/


 // 巧用前缀和，hash 表存前缀和 key: 前缀和，value: 出现次数
 
class Solution {
public:
    int pathSum(TreeNode *rt, int sum) {
        unordered_map<int, int> cnt{{0, 1}};
        return helper(rt, sum, cnt, 0);
    }

    int helper(TreeNode *rt, int sum, unordered_map<int, int> &cnt, int pre) {
        if (!rt) return 0;
        pre += rt->val;  // 前缀和
        int ans = cnt[pre - sum];
        ++cnt[pre];  // 对应计数+1
        ans += helper(rt->left, sum, cnt, pre) + helper(rt->right, sum, cnt, pre);
        --cnt[pre]; // 还原现场
        return ans; 
    }

};