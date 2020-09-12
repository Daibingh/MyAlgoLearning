#include "utils.hpp"

using namespace std;

/*
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
-------------
解法：
- 解法1：二分法
- 解法2：从右上角开始搜索（BST）
*/


// 一个矩形的左上角是该矩形中的最小元，右下角是最大元，基于此采用分治算法
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (!m) return false;
        int n = matrix[0].size();
        return helper(matrix, 0, 0 , m-1, n-1, target);
    }

    bool helper(vector<vector<int>>& matrix, int y1,int x1,int y2,int x2,int target ) {
        if (y1>y2 || x1>x2) return false;

        int mid = x1 + (x2-x1) /2;
        int l = y1, r = y2;
        while (l<=r) {
            int m = l+ (r-l)/2;
            if (matrix[m][mid] == target) return true;
            else if (matrix[m][mid] < target) {
                l = m+1;
            }
            else {
                r = m-1;
            }
        }
        // y1 x1++++++++++++++++(y1,mid)+++++++++++++++++++++y1 x2
        // +            X           +                        +
        // +++++++++++++++++++++++++r+++++++++++++++++++++++++
        // +++++++++++++++++++++++++l+++++++++++++++++++++++++
        // +                        +            X           +
        // y2 x1++++++++++++++++(y2,mid)+++++++++++++++++++++y2 x2

        // 二分搜索结束后如果没找到 *r<target<*l
        // 到 右上 和 左下 两个矩形搜索
        return helper(matrix, y1, mid+1, r, x2, target) || helper(matrix, l, x1, y2, mid-1, target );
    }
};

// 从右上角开始搜索， 从右上角看，是一个 BST 左侧 小于它，下侧 大于它
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0) {
            return false;
        }
        int i = 0;
        int j = matrix[0].size()-1;
        while(i < matrix.size() && j >= 0) {
            if(matrix[i][j] == target) {
                return true;
            }
            if(matrix[i][j] < target) {
                ++ i;
            }
            else {
                -- j;
            }
        }
        return false;
    }
};
