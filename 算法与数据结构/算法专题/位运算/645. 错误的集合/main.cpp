#include <bits/stdc++.h>

using namespace std;

/*
解法：

- 哈希
- 位运算
    - x ^ x = 0 (**偶数个异或相互抵消**)
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
        int lowbit = m & (-m);  // 靠 lowbit 将 nums 和 1~N 分为两组，一组含 a，一组含 b
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
        // 分组异或之后的结果一定是 重复数 和 缺失数
        for (const auto t : nums) 
            if (t==a) return {a, b};
        return {b, a};
    }
};