#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

int hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL)
        return 0;
    targetSum -= root->val;
    if (root->left == NULL && root->right == NULL)
        return targetSum == 0;
    return hasPathSum(root->left, targetSum) ||
           hasPathSum(root->right, targetSum);
}

int main() {}