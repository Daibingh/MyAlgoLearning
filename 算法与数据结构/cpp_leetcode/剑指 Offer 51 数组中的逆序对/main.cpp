#include <bits/stdc++.h>
using namespace std;

/*
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

示例 1:

输入: [7,5,6,4]
输出: 5
*/

// Fenwick Tree, rank 计数前缀和
class Solution {
    vector<int> tree;
public:
    int reversePairs(vector<int>& nums) {
        set<int> sorted(nums.begin(), nums.end());
        unordered_map<int, int> val2rank;
        int k = sorted.size();
        for (auto & t : sorted) {
            val2rank[t] = k--;
        }
        tree = vector<int>(sorted.size(), 0);
         int res = 0;
        for (auto & t : nums) {
            int rank = val2rank[t];
            update(rank, 1);
            res += query(rank-1);
        }
        return res;
    }

    void update(int i, int d) {
        while (i<tree.size()) {
            tree[i] += d;
            i += lowbit(i);
        }
    }

    int query(int i) {
        int ret = 0;
        while (i > 0) {
            ret += tree[i];
            i -= lowbit(i);
        }
        return ret;
    }

    static int lowbit(int x) {
        return x & (-x);
    }
};


// 归并排序
// 再合并两个有序子数组时，归并第二个数组中的元素 a 时，第一个数组剩余的元素是 a 对应的逆序对数
class Solution2 {
public:
    int reversePairs(vector<int>& nums) {
        vector<int> tmp(nums.size());
        int ret =  mergeSort(nums, tmp, 0, nums.size()-1);
        // for (auto & t : nums) cout<<t<<" ";
        return ret;
    }

    int mergeSort(vector<int>& nums, vector<int>& tmp, int left, int right) {
        if (left>=right) return 0;
        int mid = left + (right-left)/2;
        int ret  = 0;
        ret += mergeSort(nums, tmp, left, mid);
        ret += mergeSort(nums, tmp, mid+1, right);
        int l = left, r = mid+1, k=left;
        
        while (l<=mid && r <=right) {
            if (nums[l]<=nums[r]) tmp[k++] = nums[l++];    // 这里是小于等于，否则不是稳定的排序
            else { 
                tmp[k++] = nums[r++];
                ret += mid - l+1;
             }
        }
        while (l<=mid) tmp[k++] = nums[l++];
        while (r<=right) tmp[k++] = nums[r++];
        for (int i=left;i<=right;++i) nums[i] = tmp[i];
        return ret;
    }
};