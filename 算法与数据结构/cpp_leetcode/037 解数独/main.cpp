#include <bits/stdc++.h>
using namespace std;

/*
编写一个程序，通过填充空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。
*/

class Solution {
public:
    bool solveSudoku(vector<vector<char>>& board) {
        
        for (int i=0;i<9;++i) {
            for (int j=0;j<9;++j) {
                if (board[i][j]=='.') {
                    for (char c='1';c<='9';++c) {
                        if (!check(board, i, j, c)) continue;
                        board[i][j] = c;
                        if (solveSudoku(board)) return true;
                        board[i][j] = '.';
                    }
                    return false;
                }
            }
        }
        return true;  // 最后一定返回 true
    }

    bool check(vector<vector<char>>& board, int i, int j, char c) {
        int by = i/3*3, bx = j/3*3;
        for (int k=0;k<9;++k) {
            if (board[i][k]==c) return false;
            if (board[k][j]==c) return false;
            if (board[by+k/3][bx+k%3]==c) return false;  
        }
        return true;
    }
};