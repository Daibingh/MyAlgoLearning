#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][j]: (1,1) -> (i, j) 的路径个数

转移方程：

dp[i][j] = dp[i-1][j] + dp[i][j-1]  (某个状态只用到相邻状态的解，空间可优化)

边界条件：

dp[0][j] = 0
dp[i][0] = 0;
dp[1][1] = 1;
*/

// 根据对称性，做了优化，只需遍历一半，空间复杂度 O(m*n)
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m > n) return uniquePaths(n, m);
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        dp[1][1] = 1;
        for (int i=1; i<m+1; ++i) {
            if (i>1) dp[i][i] = 2 * dp[i-1][i];
            for (int j=i+1; j<n+1; ++j) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            } 
        }
        return dp.back().back();
    }
};


// 空间优化, 因为状态转移方程中某个状态只依赖于“左”和“上”，空间复杂度可以优化为 O(n)
// 滚动数组
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i=1; i<m; ++i) {
            for (int j=1; j<n; ++j) {
                dp[j] += dp[j-1];
            } 
        }
        return dp.back();
    }
};
