#include "utils.hpp"

using namespace std;


/*
实现一个基本的计算器来计算一个简单的字符串表达式的值。

字符串表达式仅包含**非负整数**，+， - ，*，/ 四种运算符和**空格**  。 整数除法仅保留整数部分。
-----------------------------------------
解法：
- 因为不考虑 括号，所以可以只用数字栈，不用符号栈
- 思想：扫描过程中优先结算乘除法，最终转化为加减法
- 具体算法：从左到右扫描，记录上一个 运算符 和 数字，当遇到新的运算符时 结算上一个数字
    - 上一个符号是 “+”、“-”，综合该符号和上一个数字，保存到栈中
    - 上一个符号是 “*”、“/”, 将栈顶的元素和上一个数字进行 乘法 或 除法 运算，更新栈顶
    - 扫描完，将栈中的元素相加
*/


class Solution {
public:
    int calculate(string s) {
        s += "@";
        int num = 0;
        char op = '+';
        stack<int> stk;
    
        for (const auto & c : s) {
            if (c == ' ') continue;
            if (isdigit(c)) num = 10*num + (c - '0');
            else {
                if (op=='+') stk.push(num);
                else if (op=='-') stk.push(-num);
                else if (op=='*') stk.top() *= num;
                else if (op='/') stk.top() /= num;
                
                num = 0;
                op = c;
                
            }
        }
        int res = 0;
        while (!stk.empty()) {
            res += stk.top();
            stk.pop();
        }
       return res;
    }
};