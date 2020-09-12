#include "utils.hpp"

using namespace std;

/*
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

*/


// 动态规划，难点在于 处理换不开的情况
// 找不开的 base case 是 那些 小于 min( coins ) 的金额，进而 所有用到该 子问题的 后续问题 也是找不开的
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {

        // dp[i] = min( dp[i-k] + 1 ), k in coins 
        vector<int> dp(amount+1, INT_MAX);  // 初始化为最大值
        dp[0] = 0;  // base case
        for (int i=1;i<=amount;++i) {
            for (int j=0;j<coins.size();++j) {
                if (coins[j]<=i && dp[i-coins[j]] !=INT_MAX ) // dp[i-coins[j]] !=INT_MAX 子问题能找开
                    dp[i] = min( dp[i-coins[j]] + 1, dp[i] );
            }
        }
        return dp.back()==INT_MAX ? -1 : dp.back();
    }
};