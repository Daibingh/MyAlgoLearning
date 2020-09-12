#include "utils.hpp"

using namespace std;

/*
给定一个未排序的整数数组，找出最长连续序列的长度。

要求算法的时间复杂度为 O(n)。

示例:

输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
--------------------------------------------
分析：
- 最初的思想方向很关键，方向错了也谈不上优化了
- 基本思想从每一个数开始递增枚举，看看数组里有没有，有就计数（关键在于“数值连续枚举”）
- 优化在于 hash set 存数，避免连续枚举到中间的数。

*/


class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set(nums.begin(), nums.end());
        int res = 0;
        for (int i=0;i<nums.size();++i) {
            int val = nums[i];
            if (num_set.find(val-1)!=num_set.end()) continue;
            int cnt = 0;
            while (num_set.find(val)!=num_set.end()) {
                ++cnt;
                ++val;
            }
            res = std::max(res, cnt);
           
        }
        return res;
    }
};