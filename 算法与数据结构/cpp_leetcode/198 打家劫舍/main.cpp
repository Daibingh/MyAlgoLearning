#include "utils.hpp"

using namespace std;


/*
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
-------------------------------
等价于从数组中去重不连续的子数组，使得和最大

*/

// 动态规划 dp[i] = max( dp[i-2]+nums[i], dp[i-1] ) ;  dp[i] 表示 从 [0,i] 能选出的最大和 
//                            i选          i不选
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i=2;i<n;++i) {
            dp[i] = max( dp[i-2]+nums[i], dp[i-1] );
        }
        return dp.back();
    }
};