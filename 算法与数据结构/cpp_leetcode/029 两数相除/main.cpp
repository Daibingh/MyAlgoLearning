#include <bits/stdc++.h>
using namespace std;

/*
给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

*/

class Solution {
public:
    int helper(int a, int b) {
        if(b==1) return a;
        if (a<b) return 0;
        int s = b;
        int ret = 1;
        while (s <=(INT_MAX>>1) && s+s<=a) {
            ret += ret;
            s += s;
        }
        return ret + helper(a-s, b);
    }

    int divide(int a, int b) {
        if (a==INT_MIN) {
            if (b==1) return a;
            if (b==-1) return INT_MAX;
            if (b==INT_MIN) return 1;
            if (b>0) return - (1 + helper(-(a+b), b));
            if (b<0) return 1 + helper(-(a-b), -b);
        }
        if (b==INT_MIN) return 0;
        if ((a^b)<0) 
            return -helper(abs(a),abs(b));
        else 
            return helper(abs(a), abs(b));
       
    }
};