#include <bits/stdc++.h>
using namespace std;


// 链表实现的线段树
// 创建 O(n) 更新、查询 O(logn)
struct SegmentTreeNode
{
    int start,end,sum;
    SegmentTreeNode* left, *right;

    SegmentTreeNode(int start, int end, int sum, SegmentTreeNode* left=nullptr, SegmentTreeNode* right=nullptr):
    start(start), end(end), sum(sum), left(left), right(right) {}
};

class NumArray {
    SegmentTreeNode* root;
    vector<int> nums;
public:
    NumArray(vector<int>& nums):nums(move(nums)) {
        if (! this->nums.empty())
            root = buildTree(0, this->nums.size()-1);
    }

    SegmentTreeNode* buildTree(int start, int end) {
        if (start==end) return new SegmentTreeNode(start,end,nums[start]);
        int mid = start + (end-start)/2;
        SegmentTreeNode* left = buildTree(start, mid);
        SegmentTreeNode* right = buildTree(mid+1, end);
        return new SegmentTreeNode(start,end, left->sum+right->sum, left, right);
    }

    void updateTree(SegmentTreeNode* root, int i, int val) {
        if (root->start==i && root->end==i) {
            root->sum = val;
            return;   // 这里要 return
        }
        int mid = root->start + ( root->end - root->start ) / 2;
        if (i <= mid) updateTree(root->left, i, val);
        else updateTree(root->right, i, val);
        root->sum = root->left->sum + root->right->sum;   // 递归完要更新 root 的sum
    }

    int sumRangeTree(SegmentTreeNode* root, int i, int j) {
        if (root->start==i && root->end==j) return root->sum;
        int mid = root->start + ( root->end - root->start ) / 2;
        if (i>mid) return sumRangeTree(root->right, i, j);
        else if (j<=mid) return sumRangeTree(root->left, i ,j);  // 等号要在算在左侧
        else return sumRangeTree(root->left, i, mid) + sumRangeTree(root->right, mid+1, j);
    }
    
    void update(int i, int val) {
        updateTree(root, i, val);
    }
    
    int sumRange(int i, int j) {
        return sumRangeTree(root, i, j);
    }
};
