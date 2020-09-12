#include "utils.hpp"

using namespace std;

/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

问总共有多少条不同的路径？
--------------------------------------------------------------------------

- 暴力递归
- 动态规划 dp[i][j] = dp[i-1][j] + dp[i][j-1];

*/


class Solution {
public:
    int uniquePaths(int m, int n) {
        return dfs(0,0, m, n);
    }
    
    int dfs(int i, int j, int m, int n) {
        if (i==m-1 || j==n-1) return 1;
        return dfs(i+1, j, m,n) + dfs(i,j+1, m,n);
    }
};


class Solution2 {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (i==0 || j==0) dp[i][j] = 1; // 在循环里处理 base case
                else
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];  // 一般情况
            }
        }
        return dp.back().back();
    }
    
};