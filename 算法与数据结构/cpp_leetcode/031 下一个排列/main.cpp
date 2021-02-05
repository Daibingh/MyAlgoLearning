#include <bits/stdc++.h>
using namespace std;


/*
1. 从后往前找 第一个满足 nums[i]<nums[i+1]
2. 从后往前找第一个满足 nums[j]>nums[i]
3. swap(nums[i], nums[j]);
4. 将 [i+1, end] 逆序
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // next_permutation(nums.begin(), nums.end());
        int i=nums.size()-2;
        for (;i>=0;--i) {
            if (nums[i]<nums[i+1]) break;
        }
        // 特殊处理
        if (i==-1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        int j=nums.size()-1;
        for (;j>i;--j) {
            if (nums[j]>nums[i]) break;
        }
        swap(nums[i], nums[j]);
        reverse(nums.begin()+i+1, nums.end());
    }
};
