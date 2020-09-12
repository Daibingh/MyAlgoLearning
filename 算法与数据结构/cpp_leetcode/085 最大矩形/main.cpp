#include "utils.hpp"
using namespace std;

/*
给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
---------------------------------
*/

// 积分图+暴力搜素（超时）
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> sum(m+1, vector<int>(n+1, 0));
        for (int i=0;i<m;++i) {
            for(int j=0;j<n;++j) {
                sum[i+1][j+1] = matrix[i][j]-'0' + sum[i][j+1] + sum[i+1][j] - sum[i][j];
            }
        } 
        int res = 0;
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if(matrix[i][j]=='0') continue;
                for (int h=m-i; h>0; --h) {
                    for (int w=n-j;w>0;--w) {
                        int s = sum[i+h][j+w] - sum[i][j+w] - sum[i+h][j] + sum[i][j];
                        if (s==w*h) {
                            res = max(res, s);
                            break;
                        }
                    }
                }
            }
        }
        return res;
    }
};