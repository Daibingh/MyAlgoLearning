#include "utils.hpp"

using namespace std;

/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。
*/

// DFS 时间复杂度 O(m*n)
class Solution {
    int m,n;
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int cnt = 0;
        m = grid.size();
        n= grid[0].size();
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                cnt += grid[i][j] - '0';
                dfs(grid, i, j);
            }
        }
        return cnt;
    }

    void dfs(vector<vector<char>>& grid, int y, int x) {
        if (y>=m || y<0 || x>=n || x<0 || grid[y][x]!='1') 
            return;
        grid[y][x] = '0';
        dfs(grid, y+1, x);
        dfs(grid, y-1, x);
        dfs(grid, y, x+1);
        dfs(grid, y, x-1);
    }
};