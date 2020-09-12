#include "utils.hpp"
using namespace std;

/*
给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
------------------
动态规划问题：
- 明确状态变量 和 选择
- 定义 dp 和 转移方程
- 确定 base case
*/


// 转化为 0-1 背包问题（每个物品要么装，要么不装）
// nums 中是否存在一个子集，使得 之和 等于 某个数
class Solution {
    unordered_set<int> mem; 
public:
    bool canPartition(vector<int>& nums) {
        int sum =0;
        for (auto & t : nums) {
            sum += t;
        }
        if (sum & 1) return false;
        sum /= 2;
        int n = nums.size();
        // 状态两维：物品，容量；外围填充
        // 定义 dp[x][y] : 对于[0,x) 物品，容量是 y, 能否（存在）恰好装满的情况 
        vector<vector<int>> dp(n+1, vector<int>(sum + 1, 0));
        // base case
        dp[0][0] = 1;
        // 遍历填表
        for (int i=1;i<=n;++i) {
            for (int j=0;j<=sum;++j) {
                // 容量比商品体积小，肯定装不了
                if (j<nums[i-1]) {
                    dp[i][j] = dp[i-1][j]; 
                }
                else {
                    // 对于第 i 个物品，有两种选择，选择 与 不选
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
                }
            }
        }
        return dp.back().back();
    }

};

/* 
01 背包原始问题：
有一个背包，他的容量为C(Capacity)。现在有n中不同的物品，编号为0…n-1，
其中每一件物品的重量为w(i)，价值为v(i)。问可以向这个背包中盛放哪些物品，
使得在不超过背包容量的基础上，物品的总价值最大。
*/

int knapsack01(const vector<int> &w, const vector<int> &v, int C) {
    
    assert( w.size() == v.size() && C >= 0 );

    if ( n == 0) {
        return 0;
    }

    int n = w.size();
    vector<vector<int>> memo( n, vector<int>(C+1,0));

    for ( int j = 0; j <= C; j++ ) {
        memo[0][j] = ( j >= w[0] ? v[0] : 0 );
    }

    for ( int i = 1; i < n; i++ ) {
        for ( int j = 0; j <= C; j++ ) {
            // 0~i这些物品容积为j的背包获得的最大值
            memo[i][j] = memo[i-1][j];
            if( j >= w[i] ) {
                memo[i][j] = max( memo[i][j], v[i] + memo[i-1][j-w[i]]);
            }
        }
    }

    return memo[n-1][C];
}
