#include "utils.hpp"
using namespace std;

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input: 

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
----------
- 动态规划两种写法，
    - 动态规划求积分图，快速求任意矩形的和，通过和判断是否全 1
    - 定义 dp[i][j] 表示 以 [i,j] 为右下角的最大全 1 矩形的边长

*/


// 动态规划体现在求积分图
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m==0) return 0;
        int n = matrix[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));  // 求 从(0,0)->[i,j] 矩形中的和，积分图
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                dp[i+1][j+1] = matrix[i][j] - '0' 
                         + dp[i][j+1]
                         + dp[i+1][j]
                         - dp[i][j];
                // cout<<dp[i+1][j+1]<<endl;
            }
        }
        int res = 0;
        // 从每个点开始，以 (i,j) 为矩形，枚举边长从大到小，更新最优解
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if(matrix[i][j]=='0') continue;
                for (int k=min(m-i, n-j); k>0;--k) {
                    int sum = dp[i+k][j+k]  // 利用积分图，求出 [i,j]->[i+k-1,j+k-1] 的矩形的和
                            - dp[i+k][j]
                            - dp[i][j+k]
                            + dp[i][j];
                    if (sum == k*k) {  // 如果矩形的和 == k^2 则该矩形是全是 1，更新结果
                        res = max(res, sum);
                        break;
                    }
                }
            }
        }
        return res;
    }
};

//  另一种动态规划，定义 dp[i][j] 表示 以 [i,j] 为右下角的最大全 1 矩形的边长
class Solution2 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m==0) return 0;
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int res =0;
        for (int i=0; i<m;++i) {
            for (int j=0;j<n;++j) {
                if (matrix[i][j]=='0') {
                    dp[i][j] = 0; // base case
                    continue;
                }
                if (i==0 || j==0) dp[i][j] = 1;  // base case
                else
                    dp[i][j] = min(min( dp[i][j-1], dp[i-1][j] ), dp[i-1][j-1]) + 1;  // 状态转移方程
                res = max(res, dp[i][j]);
            }
        }
        return res*res;
    }
};