#include "utils.hpp"

using namespace std;


/*
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
-------------------------------------------------------
*/

// 动态规划 空间 O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size()<2) return 0;
        int n = prices.size();
        int dpi1 = -prices[0];
        int dpi0 = max( 0, dpi1+prices[1] );
        dpi1 = max( dpi1, 0-prices[1] );
        int dpi0_ = 0;
        for (int i=2;i<n;++i) {
            int tmp = dpi0;  // 备份 
            dpi0 = max( dpi0, dpi1+prices[i] );
            dpi1 = max( dpi1, dpi0_-prices[i] );
            dpi0_ = tmp;
        }
        return dpi0;
    }
};


// 动态规划 空间 O(n)
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size()<2) return 0;
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        dp[1][0] = max( dp[0][0], dp[0][1]+prices[1] );
        dp[1][1] = max( dp[0][1], dp[0][0]-prices[1] );
        for (int i=2;i<n;++i) {
            dp[i][0] = max( dp[i-1][0], dp[i-1][1]+prices[i] );
            dp[i][1] = max( dp[i-1][1], dp[i-2][0]-prices[i] );
        }
        return dp.back()[0];
    }
};
