#include "utils.hpp"
using namespace std;


/*
编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为汉明重量）。
*/

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        for (;n;++cnt) n = n&(n-1);
        return cnt;
    }
};
