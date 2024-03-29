#include "utils.hpp"
using namespace std;

/*
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]
示例 2:

输入: [-1,-100,3,99] 和 k = 2
输出: [3,99,-1,-100]
解释: 
向右旋转 1 步: [99,-1,-100,3]
向右旋转 2 步: [3,99,-1,-100]
说明:

尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
要求使用空间复杂度为 O(1) 的 原地 算法。

*/


// O(k*n) 超时
class Solution1 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        for (int i=0;i<k;++i) {
            int tmp = nums[0];
            for (int j=0;j<n;++j) {
                swap(tmp, nums[(j+1)%n]);
            }
        }
    }
};

// 借助额外空间
class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> bak(nums);
        for (int i=0;i<n;++i) {
            nums[(i+k)%n] = bak[i];
        }
    }
};

// 三次翻转 !!!!!!!!!!!!!!!!!!!!!!
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());  // 全部翻转
        reverse(nums.begin(), nums.begin()+k );  // 前k个翻转
        reverse(nums.begin()+k, nums.end() );  // 剩余翻转
    }
};



