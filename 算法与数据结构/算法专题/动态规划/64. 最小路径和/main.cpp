#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][j] : 从 (0,0) -> (m-1, n-1) 的最小路径和

转移方程：

dp[i][j] = grid[i][j] + min( dp[i-1][j], dp[i][j-1] ) ;

边界条件：

dp[0][j] = sum [k=0..j] (grid[0][k])
dp[i][0] = sum [k=0..i] (grid[k][0])

*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(grid);
        for (int i=1; i<m; ++i) {
            dp[i][0] += dp[i-1][0];
        }
        for (int j=1; j<n; ++j) {
            dp[0][j] += dp[0][j-1];
        }
        for (int i=1; i<m;++i) {
            for (int j=1; j<n; ++j) {
                dp[i][j] = grid[i][j] + min( dp[i-1][j], dp[i][j-1] ) ;
            }
        } 
        return dp.back().back();
    }
};

// 空间优化 O(n)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n+1, INT_MAX);
        for (int i=1; i<m+1; ++i) {
            for (int j=1; j<n+1; ++j) {
                if (i==1 && j==1) 
                    dp[j] = grid[0][0];
                else
                    dp[j] = grid[i-1][j-1] + min( dp[j], dp[j-1] ) ;
            }
        }
        return dp.back();
    }
};