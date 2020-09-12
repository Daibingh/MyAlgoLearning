#include "utils.hpp"

using namespace std;

/*
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
*/

// 转化为 首尾不相连的问题，核心原则就是：第一个和最后一个不能同时抢。
// 取 max( 抢头不抢尾, 抢尾不抢头 )
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if(nums.size()==1) return nums[0];
        int n = nums.size();
        return max( helper(nums, 0, n-2), helper(nums, 1, n-1) );
    }

    int helper(vector<int>& a, int start, int end) {
        if (end-start+1==0) return 0;
        if (end-start+1==1) return a[start];
        int dp = max(a[start], a[start+1]);
        int dp_1 = a[start];
        for (int i=start+2;i<=end;++i) {
            int tmp = dp;
            dp = max( dp, dp_1+a[i] );
            dp_1 = tmp;
        }
        return dp;
    }
};