#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

/*
二叉树的遍历实现
    - 递归实现很方便
    - 非递归实现先序和中序较为容易，后序较复杂
*/

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v=0):val(v),left(nullptr),right(nullptr) {}
};

// 递归先序遍历
void preOrderTraversal(TreeNode* root) {
    if (root) {
        cout<<(root->val)<<endl;
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// 非递归先序遍历 另外一种写法与层序遍历类似，将 队列换成栈，先 push(root->right) 就行
void preOrderTraversal2(TreeNode* root) {

    stack<TreeNode*> S;
    TreeNode* cur = root;
    while (cur || !S.empty())  // 注意是或的关系
    {
        if (cur) {   // 一路向左走到底，访问节点并入栈
            cout<<cur->val<<endl;  // 先序遍历，第一次遇到就访问
            S.push(cur);
            cur = cur->left;  // 更新当前节点
        }
        else {
            cur = S.top()->right;  // 左边走到底了，如果栈非空，父亲节点退栈，再跳到它的右儿子节点
            S.pop();
        }                  
    }
}

// 非递归中序遍历
void inOrderTraversal2(TreeNode* root) {

    stack<TreeNode*> S;
    TreeNode* cur = root;
    while (cur || !S.empty())  // 注意是或的关系
    {
        if (cur) {   // 一路向左走到底，访问节点并入栈
            S.push(cur);
            cur = cur->left;  // 更新当前节点
        }
        else {
            cout<<S.top()->val<<endl;  // 左边走到底了，如果栈非空，父亲节点退栈，再跳到它的右儿子节点
            cur = S.top()->right;
            S.pop();
        }
    }
}


// 非递归后序遍历
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        unordered_map<TreeNode*, int> meet;  // 记录遇见的次数
        vector<int> res;
        while (root || !stk.empty()) {
            if (root && meet[root]==0) {
                stk.push(root);
                ++meet[root];
                root = root->left;
            }
            else {
                auto t = stk.top();
                if (++meet[t]==3) {  // 第三次遇见，做访问，并出栈
                    res.push_back(t->val);
                    stk.pop();
                }
                else {   // 否则是第二次，不出栈，继续向右
                    root = t->right;
                }
            }
        }
        return res;
    }
};


// 层次遍历
void layerTraversal(TreeNode* root) {
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty())
    {
        TreeNode* cur =que.front();
        que.pop();
        cout<<cur->val<<endl;
        if (cur->left) que.push(cur->left);
        if (cur->right) que.push(cur->right);
    }
}


int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);

    // preOrderTraversal(root);
    // preOrderTraversal2(root);
    // inOrderTraversal2(root);

    layerTraversal(root);

}