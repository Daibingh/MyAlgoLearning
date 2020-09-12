#include "utils.hpp"

using namespace std;

/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
----------------------------------------------------------------------------------------
*/

// 因为只能进行一次交易，所以 低价买， 高价卖 肯定利润最大
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minval = INT_MAX;
        int res = 0;
        for (const auto& p : prices) {
            res = max(res, p - minval); // 实时更新最优利润
            minval = min(minval, p);  // 更新最小值
        }
        return res;
    }
};


// 动态规划算法 空间 O(n)
// dp[i][0] 第 i 天未持股票的最大利润；dp[i][1] 第 i 天持有股票的最大利润
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        // base case
        // dp[0][0] = 0;
        dp[0][1] = - prices[0];
        for (int i=1;i<n;++i) {
            dp[i][0] = max( dp[i-1][0], dp[i-1][1]+prices[i] );  
            dp[i][1] = max( dp[i-1][1], 0-prices[i] ); // 为持有股票之前利润是 0，因为只能进行一次交易
        }
        return dp.back()[0];
    }
};

// 动态规划 空间 O(1) 因为上面状态转移只利用相邻的状态
// 下面这种写法和 第一种就很相似了
class Solution3 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        int dpi0 = 0;
        int dpi1 = - prices[0];
        for (int i=1;i<n;++i) {
            dpi0 = max( dpi0, dpi1+prices[i] );  
            dpi1 = max( dpi1, -prices[i] ); // 为持有股票之前利润是 0，因为只能进行一次交易
        }
        return dpi0;
    }
};