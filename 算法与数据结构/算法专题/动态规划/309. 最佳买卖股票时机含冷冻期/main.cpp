#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][0] : 第 i 天不持股获得的最大利润；dp[i][1] : 第 i 天持股获得的最大利润

转移方程：

dp[i][0] = max( dp[i-1][0], dp[i-1][1]+prices[i] );
dp[i][1] = max( dp[i-1][1], dp[i-2][0]-prices[i] );

边界条件：

dp[0][1] = -prices[0];
dp[1][0] = max( dp[0][0], dp[0][1]+prices[1] );
dp[1][1] = max( dp[0][1], dp[0][0]-prices[1] );

*/

class Solution {
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