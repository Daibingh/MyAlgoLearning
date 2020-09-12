#include "utils.hpp"
using namespace std;

/*
根据 百度百科 ，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态：1 即为活细胞（live），或 0 即为死细胞（dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
根据当前状态，写一个函数来计算面板上所有细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。
*/


// 位运算，利用 int 的空闲 bit 存储信息
class Solution {
    int m,n;
    vector<vector<int>> dt;
public:
    void gameOfLife(vector<vector<int>>& board) {
        m = board.size();
        n = board[0].size();
        dt = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};
        for(int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                update(board, i, j);
            }
        }
        for (auto & r : board) 
            for (auto & t : r) t >>=1;
    }

    void update(vector<vector<int>>& board, int y, int x) {
        int cnt = 0;
        for (int i=0;i<8;++i) {
            int y1 = y + dt[i][0];
            int x1 = x + dt[i][1];
            if (y1<0 || y1>=m || x1<0 || x1>=n) continue;
            if (board[y1][x1] & 1) ++cnt;
        }
        if (  ( (board[y][x] & 1) && ( cnt == 2 || cnt ==3 ) ) || ( !(board[y][x] & 1) && cnt==3 )  ) 
            board[y][x] |= 2;
    }
};