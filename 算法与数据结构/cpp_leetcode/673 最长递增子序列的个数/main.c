#include "stdio.h"
#include "math.h"

/*

给定一个未排序的整数数组，找到最长递增子序列的个数。

*/

static int dp[2005];  // 以i结尾最长递增子序列的长度
static int len[2005];  // 以i结尾的LIS的个数

int findNumberOfLIS(int* a, int n) {
    int res = 0;
    int maxLen = 1;
    for (int i=0; i<n; ++i) {
        dp[i] = 1;
        len[i] = 1;
        for (int j=0; j<i; ++j) {
            if (a[i] > a[j]) {
                // dp[i] = fmax(dp[j]+1, dp[i]);
                if (dp[j]+1 > dp[i]) {
                    dp[i] = dp[j]+1;
                    len[i] = len[j];
                } else if (dp[j]+1 == dp[i]) {
                    len[i] += len[j];
                }
            }
        }
        // maxLen = fmax(maxLen, dp[i]);
        if (dp[i] > maxLen) {
            res = len[i];
            maxLen = dp[i];
        } else if (dp[i] == maxLen) {
            res += len[i];
        }
    }
    // printf("%d\n", maxLen);
    return res;
}