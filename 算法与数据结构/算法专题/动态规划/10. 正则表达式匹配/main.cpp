#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][j]: s[:i] 与 p[:j] 是否匹配

转移方程：

dp[i][j] = p[j] == '.' && dp[i-1][j-1] ||
            p[j] == '*' && ( dp[i][j-2] || dp[i-1][j]  ) ||
            p[j] != '.' && p[j] != '*' && s[i] == p[j] && dp[i-1][j-1] ||

边界条件：

1) s="", p="" : dp[0][0]=1 ;
2) s="", p="c*a*" : dp[0][k]=1 (k=2, 4, ...)

*/

class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<int>> dp(s.size()+1, vector<int>(p.size()+1, 0));
        dp[0][0] = 1;
        // handle s="", p="c*a*..."
        for (int i=1; i<p.size(); i+=2) {
            if (p[i]=='*') dp[0][i+1] = 1;
            else break;
        }
        for (int i=1; i<s.size()+1; ++i) {
            for (int j=1; j<p.size()+1; ++j) {
                if (p[j-1]=='*') {
                    dp[i][j] =  dp[i][j-2] || ( ( p[j-2] == '.' || p[j-2] == s[i-1] ) && dp[i-1][j]);
                } else {
                    dp[i][j] = ( p[j-1] == '.' || s[i-1] == p[j-1] ) &&  dp[i-1][j-1];
                }
            }
        }
        return dp.back().back();
    }
};
