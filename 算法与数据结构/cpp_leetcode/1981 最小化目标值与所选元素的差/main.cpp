#include "utils.hpp"

using namespace std;

/*
给你一个大小为 m x n 的整数矩阵 mat 和一个整数 target 。

从矩阵的 每一行 中选择一个整数，你的目标是 最小化 所有选中元素之 和 与目标值
target 的 绝对差 。

返回 最小的绝对差 。

a 和 b 两数字的 绝对差 是 a - b 的绝对值。

--------------------------------------
动态规划，对 target 的取值进行遍历

要学会对复杂度进行估算

定义 dp[i][j] = 0~i 行是否存在和为 target 的组合

dp[i][j] = dp[i][j] || dp[i-1][j-mat[i][k]] (i = 1..N) 或者

dp[i+1][j+mat[i+1][k]] = 1 if dp[i][j] = 1; 根据已知的解，推导未知的解

*/

class Solution {
    bool dp[72][4901];

   public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int m = mat.size();
        int n = mat[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < 4901; ++j) {
                if (dp[i][j])
                    for (int k = 0; k < n; ++k) {
                        dp[i + 1][j + mat[i][k]] = 1;
                    }
            }
        }
        for (int i = 0; i < 4901; ++i) {
            if (dp[m][target + i] || (target - i >= 0 && dp[m][target - i]))
                return i;
        }
        return 0;
    }
};