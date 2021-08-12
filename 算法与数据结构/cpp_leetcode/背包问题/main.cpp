#include <bits/stdc++.h>

using namespace std;


// 0-1背包问题: 每种物品只有一个
// 恰好装满与不要求装满的**初始化不同**
int solve_01(vector<int>& weights, vector<int>& values, int capacity) {  
    int N = weights.size();
    int V = capacity;
    vector<vector<int>> dp(N+1, vector<int>(V+1, 0));  // 全初始化为零，不要求装满
    for (int i=1;i<=N;++i) {  // 外层循环遍历物品
        for (int j=1;j<=V;++j) {
            dp[i][j] = max( dp[i-1][j], j-weights[i-1]>=0 ? values[i-1]+dp[i-1][j-weights[i-1]] : 0 );  // 注意 dp 表索引与数组索引的对应关系
        }
    }
    return dp.back().back();
}

// 0-1背包，优化空间
int solve_01_2(vector<int>& weights, vector<int>& values, int capacity) {
    int N = weights.size();
    int V = capacity;
    vector<int> dp(V+1, 0);
    for (int i=0;i<N;++i) {
        for (int j=V;j>=1;--j) {  // 倒序遍历求解
            dp[j] = max( dp[j], j-weights[i]>=0 ? values[i]+dp[j-weights[i]] : 0 );  // 注意 dp 表索引与数组索引的对应关系
        }
    }
    return dp.back();
}

///////////////////////////////////////////////////////////////////////////////////
// 完全背包问题：每种物品个数无限多
int solve_comp(vector<int>& weights, vector<int>& values, int capacity) {
    int N = weights.size();
    int V = capacity;
    // dp[i] = max( dp[i], dp[i-w[j]]+v[j] )
    vector<int> dp(V+1, 0);
    for (int i=1;i<=V;++i) {
        for (int j=0;j<N;++j) {
            if (i-weights[j]>=0)
                dp[i] = max( dp[i], dp[i-weights[j]]+values[j] );
        }
    }
    return dp.back(); 
}

/////////////////////////////////////////////////////////////////////////////////
// 多重背包问题：每种物品个数有限, 可以转化为 01 背包
int solve_multi(vector<int>& nums , vector<int>& weights, vector<int>& values, int capacity) {
    int N = weights.size();
    int V = capacity;
    vector<int> dp(V+1, 0);
    for (int i=0;i<N;++i) {
        for (int k=0;k<nums[i];++k) {
            for (int j=V;j>=1;--j) {
                dp[j] = max( dp[j], j-weights[i]>=0 ? values[i]+dp[j-weights[i]] : 0 );  // 注意 dp 表索引与数组索引的对应关系
            }
        }
    }
    return dp.back();
}


/*
总结：

- 多重背包可以转换为 0-1 背包
- 完全背包外循环为容量（找零问题，每种硬币无限多）
*/


int main() {
    vector<int> weights{1,4,2,5,7};
    vector<int> values{1,5,2,6,7};
    int res = solve_01_2(weights, values, 15);
    res = solve_comp(weights, values, 15);
    vector<int> nums{3,1,2,1,1};
    res = solve_multi(nums, weights, values, 15);
    cout<<res<<endl;
    return 0;
}
