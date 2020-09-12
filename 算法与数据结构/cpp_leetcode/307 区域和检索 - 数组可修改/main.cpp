#include <bits/stdc++.h>
using namespace std;

/*
给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。

示例:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
说明:

数组仅可以在 update 函数下进行修改。
你可以假设 update 函数与 sumRange 函数的调用次数是均匀分布的。
*/

// 采用树状数组
// 更新和查询都是 O(logn)
class NumArray {
    vector<int> arr;  // 存树
    vector<int> bak;  // 存数据

    int lowbit(int x) { return x & (-x); }  // x & (-x) 取出最低位的 “1”

public:
    NumArray(vector<int>& nums): arr(nums.size()+1, 0),bak(nums.size(),0) {
        int i=0;
        for (auto & t : nums) update(i++, t);
}
    
    void update(int idx, int val) {
        int del = val - bak[idx];
        bak[idx] = val;
        idx += 1;
        while (idx < arr.size()) {
            arr[idx] += del;
            idx += lowbit(idx);
        }
    }

    int query(int idx) {
        int ret = 0;
        while (idx > 0 )
        {
            ret += arr[idx];
            idx -= lowbit(idx);
        }
        return ret;
    }
    
    int sumRange(int i, int j) {
        return query(j+1) -query(i);
    }
};

//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////
// 数组实现 线段树
class NumArray {
    vector<int> tree;
    int n;
public:
    NumArray(vector<int>& nums) {
        if (nums.empty()) return;
        n = nums.size();
        tree = vector<int>(n*4, 0);  // n*4 比较安全，不会出现越界访问
        buildTree(nums, 0, 0, n-1);
    }

    void buildTree(const vector<int>& nums, int root, int start, int end) {
        // cout<<root<<" "<<start<<" "<<end<<" "<<endl;
        if (start==end) {
            tree[root] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        int leftChd = 2*root+1, rightChd = 2*root+2;
        buildTree(nums, leftChd, start, mid);
        buildTree(nums, rightChd, mid+1, end);
        tree[root] = tree[leftChd] + tree[rightChd];
    }

    void updateTree(int root, int start, int end, int i, int val) {
        if (start==i && end==i) {
            tree[root] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        int leftChd = 2*root+1, rightChd = 2*root+2;
        if (i<=mid) updateTree(leftChd, start, mid, i, val);
        else updateTree(rightChd, mid+1, end, i, val);
        tree[root] = tree[leftChd] + tree[rightChd];
    }
    
    void update(int i, int val) {
        updateTree(0, 0, n-1, i, val);
    }

    int sumRangeTree(int root, int start, int end, int i, int j) {
        if (start==i && end==j) return tree[root];
        int mid = start + (end - start) / 2;
        int leftChd = 2*root+1, rightChd = 2*root+2;
        if (j<=mid) return sumRangeTree(leftChd, start, mid, i, j);
        else if (i>mid) return sumRangeTree(rightChd, mid+1, end, i, j);
        else return sumRangeTree(leftChd, start, mid, i, mid) + sumRangeTree(rightChd, mid+1, end, mid+1, j);
    }
    
    int sumRange(int i, int j) {
        return sumRangeTree(0, 0, n-1, i, j);
    }
};