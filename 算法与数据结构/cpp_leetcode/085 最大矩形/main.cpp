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


// 动态规划，记录每个点为底边的矩形的左右边界和高度
class Solution2 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> L(n), R(n, n), H(n);
        int res = 0;
        for (int i=0;i<m;++i) {
            int curL = 0, curR = n-1;  // 记录当前行当前列连续 “1” 的左，右边界
            for (int j=0;j<n;++j) {
                if (matrix[i][j]=='1') {
                    ++H[j];
                    L[j] = max(L[j], curL);
                }
                else {
                    H[j] = 0;
                    L[j] = 0;
                    curL = j+1;
                }
                if (matrix[i][n-j-1]=='1') {
                    R[n-j-1] = min(R[n-j-1], curR);
                }
                else {
                    R[n-j-1] = n;
                    curR = n-j-2;
                }
            }

            for (int j=0;j<n;++j) {
                res = max(res,  H[j] * ( R[j] - L[j] + 1) );
            }

        }
        return res;
    }
};