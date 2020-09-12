#include "utils.hpp"
using namespace std;

/*
峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞。

示例 1:

输入: nums = [1,2,3,1]
输出: 2
解释: 3 是峰值元素，你的函数应该返回其索引 2。

*/


// 二分法
class Solution {
public:
     int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[mid] > nums[mid + 1])  // 这里关键！
                r = mid;        // 向 [0, mid] 找 , 用区间断点逼近峰值
            else
                l = mid + 1;
        }
        return l;  // 最后 l=r=峰值
    }
};