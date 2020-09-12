#include "utils.hpp"
using namespace std;


/*
给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

 
示例 1：

输入："abc"
输出：3
解释：三个回文子串: "a", "b", "c"
示例 2：

输入："aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

*/

// 动态规划
// 状态转移方程： dp[j][i] = ( j-i<=1 || dp[j+1][i-1] ) && s[i]==s[j] ;
// base case dp[i][i] = 1;
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int res  = n;
        // base case
        for (int i=0;i<n;++i) {
            dp[i][i] = 1;
        }
        for (int i=1;i<n;++i) {
            for (int j=0;j<i;++j) {
                dp[j][i] = i-j>1 ? dp[j+1][i-1] && (s[i]==s[j]) : s[i]==s[j] ;
                if (dp[j][i]) ++res; 
            }
        }
        return res;
    }
};