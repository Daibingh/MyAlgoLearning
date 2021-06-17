

// 注意数组的初始化，尤其是最大值初始化，有符号数问题

int numSquares(int n){
    unsigned int *dp = (int*)malloc((n+1) * sizeof(unsigned int));
    memset(dp, 0xff, (n+1) * sizeof(unsigned int));
    dp[0] = 0;
    for (int i=1; i<=n; ++i) {
        int s;
        for (int j=1; (s=j*j)<=i; ++j) {
            dp[i] = fmin(dp[i], dp[i-s] + 1);
        }
        
    }
    return dp[n];
}