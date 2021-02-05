#include <bits/stdc++.h>

using namespace std;

/*
给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。

例如，给定三角形：

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 1jb1）。
*/

// dfs 记忆递归
typedef long long ll;

class Solution {
    unordered_map<ll, int> mem;
public:
    int minimumTotal(vector<vector<int>>& a) {
        int res = dfs(a, 0, 0);
        return res;
    }

    int dfs(vector<vector<int>>& a, int row, int col) {
        if (row>=a.size()) return 0;
        if (col > row) return INT_MAX;
        if (mem.count(((ll)row<<32)|col)) return mem[ ((ll)row<<32)|col ];
        int ret = a[row][col] + min( dfs(a, row+1, col), dfs(a, row+1, col+1) );
        return mem[((ll)row<<32)|col]=ret;
    }
};


// 空间复杂度 O(n), 迭代
class Solution2 {

public:
    int minimumTotal(vector<vector<int>>& a) {
        vector<int> sum(a.size(), INT_MAX);
        sum[0] = a[0][0];
        for (int i=1;i<a.size();++i) {
            for (int j=i;j>0;--j) {  // 从后往前更新
                sum[j] = a[i][j] + min(sum[j], sum[j-1]);
            }
            sum[0]+=a[i][0];
        }
        int res = INT_MAX;
        for (auto & t : sum) {
            res = min(res, t);
        }
        return res;
    }

};
