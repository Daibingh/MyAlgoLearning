
#include <bits/stdc++.h>
using namespace std;

/*
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-subsequence
*/

/*
动态规划：
定义 dp[i][j] : [i, j] 范围内的解

状态转移方程：

1. s[i] == s[j] : dp[i][j] = dp[i+1][j-1] + 2 ;
2. s[i] != s[j] : dp[i][j] = max( dp[i][j-1], dp[i+1][j] ) ;

边界条件：

dp[i][i] = 1;
dp[i][j] = 0; (i > j)

*/

class Solution {
   public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        for (int j = 0; j < n; ++j) {
            for (int i = j - 1; i >= 0; --i) {  // 注意遍历的方向！
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main(void)
{
    return 0;
}