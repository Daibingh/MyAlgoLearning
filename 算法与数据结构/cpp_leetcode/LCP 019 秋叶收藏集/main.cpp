#include <bits/stdc++.h>

using namespace std;

/*
小扣出去秋游，途中收集了一些红叶和黄叶，他利用这些叶子初步整理了一份秋叶收藏集 leaves， 字符串 leaves 仅包含小写字符 r 和 y， 其中字符 r 表示一片红叶，字符 y 表示一片黄叶。
出于美观整齐的考虑，小扣想要将收藏集中树叶的排列调整成「红、黄、红」三部分。每部分树叶数量可以不相等，但均需大于等于 1。每次调整操作，小扣可以将一片红叶**替换**成黄叶或者将一片黄叶替换成红叶。请问小扣最少需要多少次调整操作才能将秋叶收藏集调整完毕。
*/

// 动态规划
// dp[i][j]: 第i个叶子调整为状态j所需最少次数
// j={0,1,2} 分别表示 左红，中黄，右红
const int M =  1e5+1;

class Solution {
public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        vector<vector<int>> dp(n, vector<int>(3, M));
        dp[0][0] = (leaves[0]!='r');
        for (int i=1;i<n;++i) {
            dp[i][0] = dp[i-1][0] + (leaves[i]!='r');
            dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + (leaves[i]!='y');
            dp[i][2] = min( dp[i-1][1], dp[i-1][2] ) + (leaves[i]!='r');
        }
        return dp.back()[2];
    }
};

/*
反思：此题值得反思，动态规划还是很实用的！关键在于 dp 数组的定义
*/