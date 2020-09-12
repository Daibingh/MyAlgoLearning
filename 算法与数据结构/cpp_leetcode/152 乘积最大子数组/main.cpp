#include "utils.hpp"

using namespace std;


/*

给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

*/

// 动态规划解法，dp[i][j] 以 i **结尾**的子数组的最值 （最大值和最小值都要保存）
// 状态转移过程中，要考虑到当前数的 符号， 负数使得 过去的 最大值与最小值发生颠倒，
// 总之，最值在 有两种情况：1) 与上一个数构成一个子数组 2) 单独构成一个子数组 。 取两种情况的最大值
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] =dp[0][1] = nums[0];
        int res = nums[0];
        for (int i=1;i<n;++i) {
            if (nums[i]>0) {
                dp[i][0] = max( nums[i]*dp[i-1][0], nums[i] ); 
                dp[i][1] = min( nums[i]*dp[i-1][1], nums[i] ); 
            }
            else {
                dp[i][0] = max( nums[i]*dp[i-1][1], nums[i] ); 
                dp[i][1] = min( nums[i]*dp[i-1][0], nums[i] ); 
            }
            res = max(res, dp[i][0]);
        }
        return res;
    }
};