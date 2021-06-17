#include <bits/stdc++.h>

using namespace std;

/*

几张卡牌 排成一行，每张卡牌都有一个对应的点数。点数由整数数组 cardPoints 给出。

每次行动，你可以从行的开头或者末尾拿一张卡牌，最终你必须正好拿 k 张卡牌。

你的点数就是你拿到手中的所有卡牌的点数之和。

给你一个整数数组 cardPoints 和整数 k，请你返回可以获得的最大点数。
*/

// 简化问题
class Solution {
   public:
    int maxScore(vector<int>& cardPoints, int k) {
        int sum = accumulate(cardPoints.begin(), cardPoints.begin() + k, 0);
        int res = sum;
        for (int i = k - 1, j = cardPoints.size() - 1; i >= 0; --i) {
            sum = sum - cardPoints[i] + cardPoints[j--];
            res = max(res, sum);
        }
        return res;
    }
};