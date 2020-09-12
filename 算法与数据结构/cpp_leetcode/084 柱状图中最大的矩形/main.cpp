#include <bits/stdc++.h>
#include "utils.hpp"
using namespace std;


/*

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
------------------------------------------
分析：
- 利用单调栈：寻找每个位置左右两侧第一个小于它的位置，中心扩散的优化
- 相似题目：接雨水(42)

*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n,n);  // 每个点的左右边界
        stack<int> S;  // 单调递增栈
        for (int i=0;i<n;++i) {
            while (!S.empty() && heights[S.top()]>=heights[i]) {
                right[S.top()] = i;  // 当出栈时，栈顶的右边界是当前点
                S.pop();
            }
            left[i] = S.empty() ? -1 : S.top();  // 入栈时，当前点的左边界是栈顶
            S.push(i);
        }
        int res = 0;
        for (int i=0;i<n;++i) {
            res = std::max(res, (right[i]-left[i]-1)*heights[i]);  // 左右边界不算在内，所以 "-1"
        }
        return res;
    }
};

int main() {

}
