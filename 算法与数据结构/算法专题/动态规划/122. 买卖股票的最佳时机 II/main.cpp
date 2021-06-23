#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][0] : 第 i 天不持股获得的利润；dp[i][1] : 第 i 天持股获得的利润

转移方程：

dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i] );
dp[i][1] = max( dp[i-1][1], dp[i-1][0]-prices[i] );

*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i=1;i<prices.size(); ++i) {
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i] );
            dp[i][1] = max( dp[i-1][1], dp[i-1][0]-prices[i] );
        }
        return dp.back()[0];
    }
};