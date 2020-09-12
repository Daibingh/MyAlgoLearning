#include "utils.hpp"
using namespace std;

/*
给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
说明 :

数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。

*/

// 采用前缀和 + hash 表
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> sumCnt{{0,1}};
        int sum = 0;
        int res = 0;
        for (auto & t : nums) {
            sum += t; 
            res += sumCnt[sum-k];
            ++sumCnt[sum];
        }
        return res;
    }
};