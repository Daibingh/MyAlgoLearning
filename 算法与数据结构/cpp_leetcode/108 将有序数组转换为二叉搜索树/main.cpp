#include "utils.hpp"
using namespace std;


// 看成中序遍历的结果，恢复二叉树
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size()-1);
    }

    TreeNode* helper(vector<int>& nums, int l, int r) {
        if (l>r) return nullptr;
        int mid = l + (r-l)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(nums, l, mid-1);
        root->right = helper(nums, mid+1, r);
        return root;
    }
};
