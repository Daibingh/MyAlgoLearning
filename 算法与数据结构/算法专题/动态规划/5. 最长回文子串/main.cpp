#include <bits/stdc++.h>

using namespace std;

/*

定义 dp[i][j]: s[i:j] 是否是回文字符串

转移方程：

dp[i][j] = ( j-i<=2 || dp[i+1][j-1] ) && s[i] == s[j]

遍历方向：

*/

// 时间复杂度 O(n^2); 空间复杂度 O(n^2)
class Solution {
   public:
    string longestPalindrome(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        pair<int, int> range(0, 0);
        for (int j = 0; j < s.size(); ++j) {
            for (int i = 0; i <= j; ++i) {
                dp[i][j] = s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1]);
                if (dp[i][j] && range.second - range.first < j - i)
                    range = {i, j};
            }
        }
        return s.substr(range.first, range.second - range.first + 1);
    }
};

// 空间优化 O(n)
class Solution {
   public:
    string longestPalindrome(string s) {
        vector<int> dp(s.size(), 0);
        pair<int, int> range(0, 0);
        for (int j = 0; j < s.size(); ++j) {
            for (int i = 0; i <= j; ++i) {
                dp[i] = s[i] == s[j] && (j - i <= 2 || dp[i + 1]);
                if (dp[i] && range.second - range.first < j - i)
                    range = {i, j};
            }
        }
        return s.substr(range.first, range.second - range.first + 1);
    }
};
