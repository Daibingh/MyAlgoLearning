#include "utils.hpp"

using namespace std;

/*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。
--------------------------
解法：
- 斐波那契数列问题，动态规划，状态可压缩到常数空间复杂度
*/

class Solution {
public:
    int climbStairs(int n) {
        if (n==1) return 1;
        vector<int> dp(n, 0);
        dp[0] = 1;
        dp[1] = 2;
        for (int i=2;i<n;++i) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp.back();
    }
};