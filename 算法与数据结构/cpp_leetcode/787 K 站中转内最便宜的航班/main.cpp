#include <bits/stdc++.h>

using namespace std;

// dfs 超时
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int,int>>> G(n);
        for (const auto & t : flights) {
            G[t[0]].push_back({t[1], t[2]});
        }
        vector<int> vis(n, 0);
        int res = dfs(G, src, dst, k+1, vis);
        vis[src] = 1;
        return res == INT_MAX ? -1 : res;
    }

    int dfs(vector<vector<pair<int,int>>>& G, int src, int dst, int k, vector<int>& vis) {
        if (k<0) return INT_MAX;
        if (src==dst) return 0;                                                                                 
        int ret = INT_MAX;
        for (auto & p : G[src]) {
            if (vis[p.first] || p.second > ret) continue;
            vis[p.first] = 1;
            int next = dfs(G, p.first, dst, k-1, vis);
            if (next!=INT_MAX)
                ret = min( ret, p.second+next);
            vis[p.first] = 0;
        }
        return ret;
    }
};


// 动态规划方法 (贝尔曼-福特算法)
// dp[u][k] : 从 src 到 u，最多经过 k 个点的最短路径
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<int>> dp(n, vector<int>(k+1, INT_MAX));
        for (int i=0;i<k+1;++i) dp[src][i] = 0;
        for (const auto & f : flights) {
            if (f[0]==src) dp[f[1]][0] = f[2];
        }
        for (int i=1; i<k+1;++i) {
            for (const auto & f : flights) {
                if (dp[f[0]][i-1]!=INT_MAX) // 防止溢出
                    dp[f[1]][i] = min( dp[f[1]][i], dp[f[0]][i-1]+f[2] ); 
            }
        }
        return dp[dst][k] == INT_MAX ? -1 : dp[dst][k];
    }
};