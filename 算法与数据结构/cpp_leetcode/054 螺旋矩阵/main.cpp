#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

/*
上下左右边界逐渐缩减，当边界重合，循环结束
*/


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty()) return res;
        int u=0, r=matrix[0].size()-1, d=matrix.size()-1, l=0;
        while (true)
        {
            for (int i=l;i<=r;++i) res.push_back(matrix[u][i]);  // 沿上边界 左到右
            if (++u>d) break;
            for (int i=u;i<=d;++i) res.push_back(matrix[i][r]);  // 沿右边界 上到下
            if (--r<l) break;
            for (int i=r;i>=l;--i) res.push_back(matrix[d][i]);  // 沿下边界 右到左
            if (--d<u) break;
            for (int i=d;i>=u;--i) res.push_back(matrix[i][l]);  // 沿左边界 下到上
            if (++l>r) break;
        }
        return res;
    }
};


int main() {
    vector<vector<int>> v = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9,10,11,12}};
    auto res = Solution().spiralOrder(v);
    print_vec(res);
}