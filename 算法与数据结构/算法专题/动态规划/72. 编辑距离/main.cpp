#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i][j] : w1[:i], w2[:j] 最少操作数

转移方程：

dp[i][j] = min( dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1] + ( w1[i]==w2[j] : 0 : 2 ) ) ;

边界条件：

dp[0][0] = 0
dp[0][j] = j
dp[i][0] = i

*/

inline int min( int a, int b, int c) {
    return std::min(a, std::min(b, c));
}

class Solution {
public:
    int minDistance(string w1, string w2) {
        vector<vector<int>> dp(w1.size()+1, vector<int>(w2.size()+1, 0));
        for (int j=1; j<w2.size()+1;++j) dp[0][j] = j;
        for (int i=1; i<w1.size()+1;++i) dp[i][0] = i;
        for (int i=1; i<w1.size()+1; ++i) {
            for (int j=1; j<w2.size()+1; ++j) {
                dp[i][j] = min( dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + ( w1[i-1]==w2[j-1] ? 0 : 1 ) ) ;
            }
        }
        return dp.back().back();
    }
};