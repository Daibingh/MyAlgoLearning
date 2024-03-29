#include "utils.hpp"
using namespace std;


/*
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。

示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]
*/


// 交替合并，占用额外空间
// 时间 O(m+n)
class Solution2 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> tmp(m+n); 
        int k = 0, i = 0, j = 0;
        while (i<m && j<n) {
            if (nums1[i]<nums2[j]) {
                tmp[k++] = nums1[i++];
            }
            else {
                tmp[k++] = nums2[j++];
            }
        }
        while (i<m) tmp[k++] = nums1[i++];
        while (j<n) tmp[k++] = nums2[j++];
        for (int i=0;i<m+n;++i) nums1[i] = tmp[i];
    }
};

// 先合并再排序
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i=0;i<n;++i) nums1[m+i] = nums2[i];
        sort(nums1.begin(), nums1.end());
    }
};