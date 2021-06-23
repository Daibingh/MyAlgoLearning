#include <bits/stdc++.h>

using namespace std;

/*
定义 dp[i]　: 爬到第 i 阶 的方法数

转移方程：

dp[i] = dp[i-1] + dp[i-2] 

边界条件：

dp[1] =  1;
dp[0] = 1;

*/

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i=2; i<=n; ++i) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};

// 优化空间复杂度为常数
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1, 0);
        int dp1 = 1;
        int dp2 = 1;
        int res = 1;
        for (int i=2; i<=n; ++i) {
            res = dp1 + dp2;
            dp2 = dp1;
            dp1 = res;
        }
        return res;
    }
};