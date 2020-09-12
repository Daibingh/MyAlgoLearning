#include "utils.hpp"
using namespace std;

/*
给定一个二叉树，原地将它展开为一个单链表。
例如，给定二叉树

    1
   / \
  2   5
 / \   \
3   4   6
将其展开为：

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
---------------------------------------

*/

// 一种巧妙的递归写法，不好想
class Solution {
public:
    TreeNode* last = nullptr;
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        flatten(root->right);
        flatten(root->left);
        root->right = last;
        root->left = nullptr;
        last = root;
    }
};


// 先序遍历存路径，然后按顺序连起来，容易写
class Solution2 {
public:
    void flatten(TreeNode* root) {
        vector<TreeNode*> path;
        preorder(root, path);
        for (int i=1;i<path.size();++i) {
            root->right = path[i];
            root->left = nullptr;  // 左侧置空
            root = root->right;
        }
        
    }
    
    void preorder(TreeNode* root, vector<TreeNode*>& path) {
        if (root) {
            path.push_back(root);
            preorder(root->left,path);
            preorder(root->right,path);
        }
    }
};