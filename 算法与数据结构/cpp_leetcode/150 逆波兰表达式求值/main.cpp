#include "utils.hpp"
using namespace std;

/*
根据 逆波兰表示法，求表达式的值。

有效的运算符包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

 

说明：

整数除法只保留整数部分。
给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
 

示例 1：

输入: ["2", "1", "+", "3", "*"]
输出: 9
解释: 该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
*/

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (auto & s : tokens) {
            if (isdigit(s[0]) || (s[0]=='-' && s.size()>1) ) {
                stk.push(stoi(s));
            }
            else {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();
                stk.push( calc(a, b, s[0]) );
            }
        }
        return stk.top();
    }

    int calc(int a, int b, char c) {
        if (c=='+') return a+b;
        else if (c=='-') return a-b;
        else if (c=='*') return a*b;
        else return a/b;
    }

};