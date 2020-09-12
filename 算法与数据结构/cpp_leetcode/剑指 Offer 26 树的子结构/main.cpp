#include <bits/stdc++.h>
using namespace std;


/*
输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:

     3
    / \
   4   5
  / \
 1   2
给定的树 B：

   4 
  /
 1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

*/


// 递归
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!B) return false;
        return helper(A, B, B);
    }

    bool helper(TreeNode* A, TreeNode* B, TreeNode* rootB) {  // 参数持有一个 rootB
        if (!A) return !B;
        if (!B) return true;
        return A->val == B->val && helper(A->left, B->left, rootB) && helper(A->right, B->right, rootB) 
                 ||  helper(A->left, rootB, rootB) || helper(A->right, rootB, rootB); 
    }

};