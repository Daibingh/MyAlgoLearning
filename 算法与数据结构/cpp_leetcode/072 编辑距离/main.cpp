#include "utils.hpp"
#include <bits/stdc++.h>

using namespace std;

/*
给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
-------------
分析：

- 动态规划

*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size()+1, vector<int>(word2.size()+1, 0));
        for (int i=1;i<=word1.size();++i) dp[i][0] = i;
        for (int i=1;i<=word2.size();++i) dp[0][i] = i;
        for (int i=1;i<=word1.size();++i) {
            for (int j=1;j<=word2.size();++j) {
                if (word1[i-1]==word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = findMin(dp[i][j-1], dp[i-1][j], dp[i-1][j-1])+1;
                }
            }
        }
        return dp.back().back();
    }
    
    int findMin(int a, int b, int c) {
        return std::min( std::min(a, b) , c);
    }
};

int main() {
    
}