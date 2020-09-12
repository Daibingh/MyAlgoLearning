#include "utils.hpp"
using namespace std;

/*

给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。
-------------------------------
- 动态规划
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));

        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (i==0 && j==0) dp[i+1][j+1] = grid[0][0];
                else
                dp[i+1][j+1] = grid[i][j] + min(dp[i][j+1], dp[i+1][j]);
            }
        }
        return dp.back().back();
    }
};