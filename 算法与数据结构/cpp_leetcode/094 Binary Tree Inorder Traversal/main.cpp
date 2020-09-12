#include "utils.hpp"
using namespace std;

/*
二叉树中序遍历
*/

// 递归
class Solution {
    vector<int> path;
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root) {
            inorderTraversal(root->left);
            path.push_back(root->val);
            inorderTraversal(root->right);
        }
        return path;
    }
};

// 非递归
class Solution2 {
    
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> path;
        stack<TreeNode*> stk;
        while (root||!stk.empty()) {
            while (root) {
                stk.push(root);
                root = root->left;
            }
            if (!stk.empty()) {  // 这里是 if 不是 while ！！！
                path.push_back(stk.top()->val);  //  中序遍历 出栈时访问，先序遍历是入栈时访问
                root = stk.top()->right;
                stk.pop();
            }
        }
        return path;
    }   
};