#include "utils.hpp"

using namespace std;


/*
给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

*/

// O(1) 常数空间
// 左右累乘，一次遍历
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> out(n, 1);
        int left = 1, right = 1;
        for (int i=0;i<n;++i) {
            out[i] *= left;
            left *= nums[i];
            out[n-i-1] *= right;
            right *= nums[n-i-1];
        }
        return out;
    }
};