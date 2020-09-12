#include "utils.hpp"

using namespace std;

/*
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

*/


// 动态规划：dp[i] = min ( dp[i-k]+1 ) k in [1,4,...,<=i] 
// O(n*sqrt(n))
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int i=1;i<=n;++i) {
            for (int j=1;j*j<=i;++j) {
                dp[i] = min( dp[i-j*j]+1, dp[i] );
            }
        }   
        return dp.back();
    }
};