#include "utils.hpp"

using namespace std;

/*
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

--------------------------------------

分析：
- 与两数之和不同的是 它要求输出数值，不是索引，因此可以进行排序
- 排序 + 双指针
- 难点在于去重：
    - 首先保证 第一个枚举的数字不和上一次重复
    - 首数固定时，左右相加满足，左右边界要不重复

*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for (int i=0;i<nums.size();++i) {
            if (i>0 && nums[i]==nums[i-1]) continue;
            int rest = -nums[i];
            int l = i+1, r = nums.size()-1;
            while (l<r) {
                int sum = nums[l] + nums[r];
                if (sum==rest) {
                    res.push_back({nums[i], nums[l], nums[r]});
                    ++l;  // 当左右指针满足条件时，要同时移动，且保证都不重复
                    --r;
                    while (l<r && nums[l]==nums[l-1]) ++l;
                    while (l<r && nums[r]==nums[r+1]) --r;
                }
                else if (sum<rest) {
                    ++l;
                }
                else --r;
                
            }
        }
        return res;
    }
};


///////////////////////////////////////////////////////////////////////
// 另一种写法
class Solution2 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size()<3) return {};
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i=0;i<nums.size()-2;++i) {
            if (i>0 && nums[i]==nums[i-1]) continue;  // 去重！
            searchTwo(nums, res, i);
        }
        return res;
    }

    void searchTwo(const vector<int>& nums, vector<vector<int>>& res, int i) {
        int target = 0-nums[i];
        int l = i+1, r = nums.size()-1;
        while (l<r) {
            if (nums[l]+nums[r]==target) {
                res.push_back({nums[i], nums[l], nums[r]});
                ++l;
                --r;
                // 去重！！！ 
                while (l<r && nums[l]==nums[l-1]) ++l;
                while (l<r && nums[r]==nums[r+1]) --r;
            }
            else if (nums[l]+nums[r]<target) {
                ++l;
            }
            else {
                --r;
            }
        }
    }
};