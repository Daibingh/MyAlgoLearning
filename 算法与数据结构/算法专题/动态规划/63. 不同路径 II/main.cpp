#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][j] : (0,0) -> (m-1, n-1) 的路径数

转移方程：

dp[i][j] = G[i][j] == 1 ? 0 : dp[i-1][j] + dp[i][j-1] ;

边界条件:

dp[0][j] = 0
dp[i][0] = 0
dp[1][1] = 1;

*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.back().back() == 1 || obstacleGrid[0][0] == 1) return 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i=1;i<m+1;++i) {
            for (int j=1; j<n+1;++j) {
                if (i==1 && j==1) dp[i][j] = 1;
                else {
                    dp[i][j] = obstacleGrid[i-1][j-1] == 1 ? 0 : dp[i-1][j] + dp[i][j-1] ;
                }
            }
        }
        return dp.back().back();
    }
};

// 空间优化 O(n)
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.back().back() == 1 || obstacleGrid[0][0] == 1) return 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<int> dp(n+1, 0);
        for (int i=1;i<m+1;++i) {
            for (int j=1; j<n+1;++j) {
                if (i==1 && j==1) dp[j] = 1;
                else {
                    dp[j] = obstacleGrid[i-1][j-1] == 1 ? 0 : dp[j] + dp[j-1] ;
                }
            }
        }
        return dp.back();
    }
};