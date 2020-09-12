#include "utils.hpp"
using namespace std;

/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。

*/

// 左括号就入栈，右括号就比较栈顶，然后出栈
class Solution {
public:
    bool isValid(string s) {
        if (s.empty()) return true;
        if (s.size() & 1) return false;

        unordered_map<char, char> m = {{'(', ')'},{'[', ']'},{'{', '}'}};

        stack<int> stk;
        for (const auto & c : s) {
            if (m.count(c)) stk.push(c);
            else if (stk.empty() || m[stk.top()] != c) return false;
            else stk.pop();
        }
        return stk.empty();
    }
};