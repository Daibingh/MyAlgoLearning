#include "utils.hpp"
using namespace std;

/*
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。
对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
*/

// 回溯 递归 记忆搜索
class Solution {
    unordered_map<long long, int> mem;
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        return helper(nums, S, 0);
    }

    int helper(vector<int>& nums, long long S, int i) {
        if (mem.count(20*S+i)) return mem[20*S+i];
        if (i==nums.size()) {
            if (S==0) return 1;
            else return 0;
        }

        int ret = helper(nums, S+nums[i], i+1) + helper(nums, S-nums[i], i+1);
        return mem[20*S+i] = ret;
    }
};