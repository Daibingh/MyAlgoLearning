#include "utils.hpp"

using namespace std;


/*
实现一个基本的计算器来计算一个简单的字符串表达式的值。

字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。
---------------------------------------------------------------------
此题不考虑乘除法，因此除了遇到 “()”, 运算都可以直接按顺序算出
*/


// 只考虑 "+", "-"
class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int res = 0, n = s.size(), sign = 1;
        for(int i=0; i<n; i++) {
            int num = 0;
            if(s[i] >= '0') {
                while(i<n && s[i] >= '0') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                i--;
                res += sign * num;
            }
            else if(s[i] == '+') sign = 1;
            else if(s[i] == '-') sign = -1;
            else if(s[i] == '(') {
                st.push(res);
                st.push(sign);
                res = 0;
                sign = 1;
            }
            else if(s[i] == ')') {
                res *= st.top(); st.pop();
                res += st.top(); st.pop();
            }
        }
        return res;
    }
};



// 如果考虑 乘除法，常规做法是 两个栈处理，

class Solution2 {
public:
    int calculate(string s) {

        unordered_map<char, int> order = {{'+', 1},
                              {'-', 1},
                              {'*', 2},
                              {'/', 2}};
        stack<char> stk_op;
        stack<int> stk_num;
        for (int i=0;i<s.size();++i) {
            char c = s[i];
            if (c == ' ') continue;   // 空格跳过
            if (isdigit(c)) {
                int num = 0;
                while (i<s.size() && isdigit(s[i])) {
                    num = 10 * num + (s[i] - '0');
                    ++i;
                }
                --i;
                stk_num.push(num);
            }
            else if (c == '(') {
                stk_op.push(c); 
                if (s[i+1] == '-') stk_num.push(0);     // 防止出现 "(-"
            }
            else if (c == ')') {
                while (stk_op.top() != '(') calc(stk_op, stk_num);
                stk_op.pop();    
            }
            else {
                while (!stk_op.empty() && order[stk_op.top()]>=order[c] && stk_op.top()!='(')  calc(stk_op, stk_num);
                stk_op.push(c);
            }
        }

        while (!stk_op.empty()) calc(stk_op, stk_num); 
        return stk_num.top();
        
    }

    void calc(stack<char>& stk_op, stack<int>& stk_num) {
        int b = stk_num.top();
        stk_num.pop();
        int a = stk_num.top();
        stk_num.pop();
        char op = stk_op.top();
        stk_op.pop();
        if (op=='+') stk_num.push( a+b );
        else if (op=='-') stk_num.push(a-b);
        else if (op=='*') stk_num.push( a*b );
        else if (op=='/') stk_num.push(a/b);
    }

};


int  main() {
   cout<< Solution2().calculate("1+1-4")<<endl;
}