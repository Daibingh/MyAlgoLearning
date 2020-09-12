#include "utils.hpp"

using namespace std;


/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
*/


// 连续利润累加
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        for (int i=1;i<prices.size();++i) {
            if (prices[i]>prices[i-1])
                res += prices[i]-prices[i-1];
        }
        return res;
    }
};

// 动态规划 空间 O(n)
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for (int i=1;i<n;++i) {
            dp[i][0] = max( dp[i-1][0], dp[i-1][1]+prices[i] );
            dp[i][1] = max( dp[i-1][1], dp[i-1][0]-prices[i] );
        }
        return dp.back()[0];
    }
};

// 动态规划 空间 O(1)
class Solution3 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        int dpi0 = 0;
        int dpi1 = - prices[0];
        for (int i=1;i<n;++i) {
            dpi0 = max( dpi0, dpi1+prices[i] );
            dpi1 = max( dpi1, dpi0-prices[i] );
        }
        return dpi0;
    }
};