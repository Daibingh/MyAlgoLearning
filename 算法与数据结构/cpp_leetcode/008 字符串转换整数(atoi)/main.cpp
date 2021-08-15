#include "utils.hpp"

using namespace std;

/*
- 思想: 先过滤掉空白，定位到第一个数字，同时确定 sign；然后累加就和
- 考察字符转整数，如何防止溢出
- O(n), O(1)
*/

class Solution {
public:
    int myAtoi(string str) {
        auto it = str.begin();
        int sign = 1;
        for (;it!=str.end();++it) {
            if (*it==' ') continue;
            if (*it>='0' && *it <='9') break;
            else if (*it=='+') {
                ++it;
                break;
            }
            else if (*it == '-') {
                sign = -1; 
                ++it;
                break;
            } else {
                return 0;
            }
        }
        int res = 0;
        for (;it!=str.end();++it) {
            if (*it<'0' || *it >'9') break;
            if (sign==1 && (res > INT_MAX/10 || (res==INT_MAX/10 && *it>='7'))) return INT_MAX;
            if (sign==-1 && (res > INT_MAX/10 || (res==INT_MAX/10 && *it>='8'))) return INT_MIN;  // 负数一侧多个“1”
            res = res*10 + (*it-'0');  // 这里一定要加 “()” 先减后加防溢出
        }
        return sign*res;
    }
};


int main() {
    string str = "-2147483648"; //"   -123abf";
    cout<< Solution().myAtoi(str)<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
- 补充另一种解法: 有限状态机 https://leetcode-cn.com/problems/string-to-integer-atoi/solution/zi-fu-chuan-zhuan-huan-zheng-shu-atoi-by-leetcode-/
- 类似一种模板化化的通用解法：划分几个状态，将字符看作输入，建立 状态 s--(输入)--> s' 转化的映射表，程序中通过查表代替原来的 "if else".
*/

class Automaton {
    string state = "start";
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };

    int get_col(char c) {
        if (isspace(c)) return 0;
        if (c == '+' or c == '-') return 1;
        if (isdigit(c)) return 2;
        return 3;
    }
public:
    int sign = 1;
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution2 {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};
