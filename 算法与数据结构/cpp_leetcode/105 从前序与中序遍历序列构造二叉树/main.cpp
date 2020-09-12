#include "utils.hpp"

using namespace std;


/*
根据一棵树的前序遍历与中序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

           l1         r1
preorder:  O LLLLL RRRR
inorder :  LLLLL O RRRR
           l2   idx   r2
*/


class Solution {
    unordered_map<int, int> val2idx;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i=0;i<inorder.size();++i) {
            val2idx[inorder[i]] = i;
        }
        return helper(preorder, inorder, 0, preorder.size()-1, 0, inorder.size()-1);
    }

    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int l1, int r1, int l2, int r2) {
        if (l1>r1) return nullptr;
        int val = preorder[l1];
        int idx = val2idx[val];
        int n_left = idx - l2;
        TreeNode* root = new TreeNode(val);
        root->left = helper(preorder, inorder, l1+1, l1+n_left, l2, idx-1);
        root->right = helper(preorder, inorder, l1+n_left+1, r1, idx+1, r2);
        return root;
    }
};