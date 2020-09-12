#include <bits/stdc++.h>
#include "utils.hpp"
using namespace std;

/*

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
-------------------------------
- 单调栈解法
- 相似题目：084 柱状图中最大的矩形

*/

class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> S;
        int res = 0;
        for (int i=0;i<height.size();++i) {
            while (!S.empty() && height[S.top()] < height[i]) {
                int cur = S.top();
                S.pop();
                if (S.empty()) break;
                int l = S.top();
                res += (std::min(height[l], height[i]) - height[cur]) * (i-l-1);
            }
            S.push(i);
        }
        return res;
    }
};


// 问题抽象：找出每个位置 左侧最大和右侧最大之中的较小者
// 双指针，左右交替移动，计算每个位置上盛水量，然后累加
class Solution2 {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int l = 0, r = n-1;
        int lMax = 0, rMax = 0;
        int res = 0;
        while (l<=r) {
            if (lMax < rMax) {
                lMax = std::max(lMax, height[l]);
                res += lMax - height[l];
                ++l;
            }
            else {
                rMax = std::max(rMax, height[r]);
                res += rMax - height[r];
                --r;
            }
        }
        return res;
    }
};