#include "utils.hpp"
using namespace std;

/*
不使用运算符 + 和 - ​​​​​​​，计算两整数 ​​​​​​​a 、b ​​​​​​​之和。

示例 1:

输入: a = 1, b = 2
输出: 3

*/


// 位运算
// a + b = (a&b)<<1 + a^b = ...
class Solution {
public:
    int getSum(unsigned int a, unsigned int b) {
         if (!a) return b;
         return getSum( (a&b)<<1, a^b );
    }
};