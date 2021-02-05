#include <bits/stdc++.h>

using namespace std;


/*
给定一个整数矩阵，找出最长递增路径的长度。
对于每个单元格，你可以往上，下，左，右四个方向移动。 
你不能在对角线方向上移动或移动到边界外（即不允许环绕）。
*/


// 记忆 dfs，从底部返回深度
class Solution {
    int m,n;
    vector<vector<int>> mem;
    vector<vector<int>> D;
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        m = matrix.size();
        n = matrix[0].size();
        mem = vector<vector<int>>(m, vector<int>(n));   // 记录以i,j为起点的路径长度
        D = {{0, 1},{1, 0},{-1, 0},{0, -1}};
        int res = 0;
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                res = max( dfs(matrix, i, j), res );  
            }
        }
        return res;
    }

    int dfs(vector<vector<int>>& matrix, int i, int j) {
        if (mem[i][j]>0) return mem[i][j];
        int ret = 1;
        for (auto& d : D) {
            int y = i+d[0];
            int x = j+d[1];
            if (y>=0 && y<m && x>=0 && x<n && matrix[y][x]>matrix[i][j]) {
                ret = max( 1 + dfs(matrix, y, x), ret );  // 一开始这里写错了！！！ "1+" 应在 max() 里边
            }
        }
        return mem[i][j] = ret;
    }
};