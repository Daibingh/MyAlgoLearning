#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

/*
给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

若这两个字符串没有公共子序列，则返回 0。
-----------------------------------
题解：
- 动态规划
- 类似：最长公共连续子序列（子串）, 最长递增子序列(300), 最大子序列和(53)
*/


class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1, 0));  // dp[i][j] 表示 [0,i] [0,j] 子问题的解
        for (int i=0;i<text1.size();++i) {
            for (int j=0;j<text2.size();++j) {
                if (text1[i]==text2[j]) {
                    dp[i+1][j+1] = 1+ dp[i][j];
                } else dp[i+1][j+1] = std::max(dp[i][j+1],dp[i+1][j]);
            }
        }
        return dp.back().back();
    }
};


int main() {
    cout<<Solution().longestCommonSubsequence("abcde", "ace")<<endl;
}