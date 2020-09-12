#include "bits/stdc++.h"
using namespace std;

/*
给定一个包含 0, 1, 2, ..., n 中 n 个数的序列，找出 0 .. n 中没有出现在序列中的那个数。
-----------------------------------
- 0 ^ n = n 与零异或是它本身
- n ^ n = 0 相同的数异或得零
*/

// 异或运算
class Solution2 {
public:
    int missingNumber(vector<int>& nums) {
        int res = nums.size();
        for (int i=0;i<nums.size();++i) {
            res ^= nums[i];
            res ^= i;
        }
        return res;
    }
};

// 求和
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = nums.size();
        for (int i=0;i<nums.size();++i) {
            res -= nums[i];
            res += i;
        }
        return res;
    }
};
