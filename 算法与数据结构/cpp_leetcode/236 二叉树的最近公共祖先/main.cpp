#include "utils.hpp"

using namespace std;

/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
------------------------------------------------------------------------------
解法：
- 递归！！！
- 哈希存父节点地址，反向遍历

*/

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // base case
        if(!root)
            return nullptr;
        if(root == p || root == q) 
            return root;

        // 递归 
        TreeNode* left =  lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 利用递归的结果返回
        if(!left)  // 左侧为空，说明 p, q 都在右边
            return right;
        if(!right)
            return left;      
        if(left && right) // p 和 q 在两侧
            return root;
        
        return nullptr; // 必须有返回值
    }
};
