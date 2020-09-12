#include "utils.hpp"
using namespace std;

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
----------------------------------------------------------------
思想：dfs

写递归函数要明确几点
- 接口设计
- 递归出口
- 递归之前做什么
- 怎么调用递归
- 递归的结果如何利用

*/


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        for (int i=0;i<m;++i) 
        {
            for (int j=0;j<n;++j) {
                if (search(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }

    bool search(vector<vector<char>>& board, string& word, int y, int x, int d) {
        if (y<0 || y>=m || x<0 || x>=n || word[d]!=board[y][x]) return false;  // 越界或当前字符不相等 return False
        if (word.size()-1 == d) return true;  // 匹配到最后一个字符 return True
        char bak = board[y][x];  // 递归之前屏蔽当前字符
        board[y][x] = 0;
        bool fnd = search(board, word, y-1, x, d+1)  // 往下递归
                || search(board, word, y+1, x, d+1)
                || search(board, word, y, x-1, d+1)
                || search(board, word, y, x+1, d+1);
        board[y][x] = bak;  // 递归结束，恢复当前字符
        return fnd;
    }

private:
    int m,n;
};