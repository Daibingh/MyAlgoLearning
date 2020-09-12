
#include "utils.hpp"
using namespace std;

/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row
----------------------------------------------------------------------------------
思想：看出一维数组，直接二分法
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m==0) return false;
        int n = matrix[0].size();
        int l = 0, r = m*n-1;
        while (l <= r) {
            int mid = l + (r-l)/2;
            int val = matrix[mid/n][mid%n];  // 一维 转 二维 坐标
            if (target == val) return true;
            else if (target < val) {
                r = mid -1;
            }
            else {
                l = mid +1;
            }
        }
        return false;
    }
};
