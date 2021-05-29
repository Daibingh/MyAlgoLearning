#include "utils.hpp"

using namespace std;

/*
给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为
0。请使用原地算法。
------------------------------------------------------------------------------------
- 关键在于要求原地算法
- 以第一行、第一列作为，列，行的标记，第一行和第一列用额外的变量标记
*/

class Solution {
   public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool row_flag = false, col_flag = false;
        for (int i = 0; i < matrix[0].size(); ++i) {
            if (!matrix[0][i]) {
                row_flag = true;
                break;
            }
        }
        for (int i = 0; i < matrix.size(); ++i) {
            if (!matrix[i][0]) {
                col_flag = true;
                break;
            }
        }

        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (!matrix[i][j]) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 从 1 开始
        for (int i = 1; i < matrix.size(); ++i) {
            if (!matrix[i][0])
                for (int j = 0; j < matrix[0].size(); ++j)
                    matrix[i][j] = 0;
        }

        // 从 1 开始
        for (int j = 1; j < matrix[0].size(); ++j) {
            if (!matrix[0][j])
                for (int i = 0; i < matrix.size(); ++i)
                    matrix[i][j] = 0;
        }

        if (row_flag)
            for (int j = 0; j < matrix[0].size(); ++j)
                matrix[0][j] = 0;

        if (col_flag)
            for (int i = 0; i < matrix.size(); ++i)
                matrix[i][0] = 0;
    }
};