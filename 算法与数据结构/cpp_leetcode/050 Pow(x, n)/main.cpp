#include "utils.hpp"

using namespace std;


/*
- 快速幂

*/

// 递归版
class Solution {
public:
    double myPow(double x, int n) {                     
        if (!n) return 1;
        double y = myPow(x, n/2);
        y = y*y;
        if (n & 1) return y* (n >0 ? x : 1/x);
        return y;
    }
};


// 非递归 x^7, 7 (0111), x^1 * x^2 * x^4
class Solution2 {
public:
    double quickMul(double x, long long N) {
        double ans = 1.0;
        // 贡献的初始值为 x
        double w = x;
        // 在对 N 进行二进制拆分的同时计算答案
        while (N > 0) {
            if (N % 2 == 1) {
                // 如果 N 二进制表示的最低位为 1，那么需要计入贡献
                ans *= w;
            }
            // 将贡献不断地平方
            w *= w;
            // 舍弃 N 二进制表示的最低位，这样我们每次只要判断最低位即可
            N /= 2;
        }
        return ans;
    }

    double myPow(double x, int n) {
        long long N = n;  // 为了避免 int 转负数溢出，转 long long
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};
