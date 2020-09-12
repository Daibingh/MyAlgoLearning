
#include "utils.hpp"
using namespace std;


/*
给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。

找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:

X X X X
X O O X
X X O X
X O X X
运行你的函数后，矩阵变为：

X X X X
X X X X
X X X X
X O X X
解释:

被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

*/


// 从边界入手 dfs
class Solution {
    int m,n;
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        m = board.size();
        n = board[0].size();
        for (int i=0;i<n;++i) {
            dfs(board, 0, i);
            dfs(board, m-1, i);
        }
        for (int i=0;i<m;++i) {
            dfs(board, i, 0);
            dfs(board, i, n-1);
        }
        for (auto & row : board) {
            for (auto & e : row) {
                if (e=='O') e = 'X';
            }
        }
        for (auto & row : board) {
            for (auto & e : row) {
                if (e=='#') e = 'O';
            }
        }
    }

    void dfs(vector<vector<char>>& board, int y, int x) {
        if (y<0 || y>=m || x<0 || x>=n || board[y][x]!='O') return;
        board[y][x] = '#';
        dfs(board, y+1, x);
        dfs(board, y-1, x);
        dfs(board, y, x+1);
        dfs(board, y, x-1);
    }
};


// 直接 DFS 判断包围有问题
// 问题代码！！！！！！！！！！！！！！！！！！
class Solution {
    int m , n;
public:
    void solve(vector<vector<char>>& board) {
        print(board);
        if (board.empty()) return;
        m = board.size();
        n = board[0].size();
        for (int i=1;i<m-1;++i) {
            for (int j=1;j<n-1;++j) {
                if (board[i][j] == 'O') 
                    dfs(board, i, j);
            }
        }
        // for (auto & row : board) {
        //     for (auto & e : row) {
        //         if (e=='#') e = 'O';
        //     }
        // }
        cout<<"----------------------------------"<<endl;
        print(board);
    }

    bool dfs(vector<vector<char>>& board, int y, int x) {
        if (y<0 || y>=m || x<0 || x>=n ) return true;
        if (board[y][x] == '#' || board[y][x] == 'X') return false;  // 这里不应直接返回 False，不确定！
        
        char ch = board[y][x];
        board[y][x] = '#';
        bool reachMargin = dfs(board, y+1, x) 
                        || dfs(board, y-1, x)
                        || dfs(board, y, x+1)
                        || dfs(board, y, x-1);
        if (!reachMargin) board[y][x] = 'X';
        else board[y][x] = ch;
        // cout<<y<<", "<<x<<" "<<reachMargin <<endl;
        print(board);
        return reachMargin;
    }

    void print(vector<vector<char>>& board) {
        for (auto & row : board) {
            for (auto & e : row) {
                cout<< e<< "  ";
            }
            cout<<endl;
        }
    }
};