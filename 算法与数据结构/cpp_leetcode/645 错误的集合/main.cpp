#include <bits/stdc++.h>

using namespace std;

/*

集合 s 包含从 1 到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，导致集合 丢失了一个数字 并且 有一个数字重复 。

给定一个数组 nums 代表了集合 S 发生错误后的结果。

请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。
---

解法：

- 哈希
- 位运算
    - x ^ x = 0 (偶数个异或相互抵消)
    - 0 ^ x = x
    - lowbit = x & (-x)
*/

// 位运算解法
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int m = 0;
        // m = nums[0] ^ ... ^ nums[N-1] ^ 1 ^ ... ^N <==> a ^ b  ( 重复数与缺失数的异或值)
        for (int i=0;i<nums.size();++i) {
            m ^= i+1;
            m^= nums[i];
        }
        int lowbit = m & (-m);  // 靠 lowbit 区分 a, b
        int a = 0, b = 0;
        // 分成两组, 分别进行异或运算
        for (const auto t : nums) {
            if (t & lowbit) a ^= t;  // 这里是 & ！！！
            else b ^= t;
        }
        for (int i=1;i<=nums.size();++i) {
            if (i & lowbit) a ^= i;
            else b ^= i;
        }
        for (const auto t : nums) 
            if (t==a) return {a, b};
        return {b, a};
    }
};