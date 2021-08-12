#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
        int old = grid[r0][c0];
        travel(grid, r0, c0, old);
        for (auto & r : grid)
            for (auto & k : r )
                if (k==-2) k = color;
        return grid;
    }

    bool travel(vector<vector<int>>& grid, int y, int x, int old) {
        if (y<0 || y>=grid.size() || x<0 || x>=grid[0].size()) return true;  // 到达外部边界
        if (grid[y][x]!=old) return grid[y][x] > 0;  // != old: 1) 走过(-1)；2) 边界(-2) 3) 其它颜色(>0),内部边界 
        grid[y][x] = -1;  // 走过标记为 -1
        bool f1 = travel(grid, y-1, x, old);
        bool f2 = travel(grid, y, x+1, old);
        bool f3 = travel(grid, y+1, x, old);
        bool f4 = travel(grid, y, x-1, old);
        grid[y][x] = old;  // 回溯后，复原走过的标记
        if ( f1 || f2 || f3 || f4 )  // 这里不能直接 对 travel() 进行 || , 因为有短路效应，必须提前计算
            grid[y][x] = -2;   // 边界标记为 -2
        return false;
    }
};