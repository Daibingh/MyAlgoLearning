#include <bits/stdc++.h>
using namespace std;


/*
判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

*/

// 数组 hash，结合位运算
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
       vector<int> row(9);
       vector<int> col(9);
       vector<int> cub(9);
       for (int i=0;i<9;++i) {
           for (int j=0;j<9;++j) {
               if (board[i][j]=='.') continue;
               int bit =  1<<(board[i][j] - '0');
               if (row[i] & bit) return false;
               if (col[j] & bit) return false;
               if (cub[i/3*3+j/3] & bit) return false;   // 计算第几个 cube (i,j) -> i/3*3+j/3
               row[i] |= bit;
               col[j] |= bit;
               cub[i/3*3+j/3] |= bit;
           }
       }
       return true;
    }
};