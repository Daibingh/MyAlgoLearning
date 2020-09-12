#include "utils.hpp"

using namespace std;


/*
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

*/


// 用栈实现，数组模拟栈，方便从底部开始遍历
class Solution {
public:
    string decodeString(string s) {
        vector<string> stk;  // vector 模拟栈
        for (int i=0;i<s.size();++i) {
            if ( isdigit(s[i]) ) {
                string num;
                while ( isdigit(s[i]) ) {
                    num += s[i];
                    ++i;
                }
                stk.push_back(num);
                --i;
            }
            else if (s[i]!=']') {
                stk.push_back(string(1, s[i]));
            }
            else {
                // 这里是关键！
                // 将 "[ ]" 之间的 字符串先用 vector 暂存，然后翻转，注意不要之间用 string 拼接然后翻转，这样
                // 每个字符串内部的顺序也反了
                vector<string> tmp;
                while (stk.back()!="[") {
                    tmp.push_back( stk.back() );
                    stk.pop_back();
                }
                stk.pop_back();
                int cnt = stoi(stk.back());
                stk.pop_back();
                reverse(tmp.begin(), tmp.end());
                stk.push_back( repeat(join(tmp), cnt) );  // 拼接字符串，重复 cnt 次，在此放入栈中
            }
        }
        string res;
        for (const auto & t : stk) {
            res += t;
        }
        return res;
    }

    string repeat(string s, int n) {
        string ret;
        for (int i=0;i<n;++i) {
            ret += s;
        }
        return ret;
    }

    string join(vector<string>& v) {
        string ret;
        for (const auto & t : v) {
            ret += t;
        }
        return ret;
    }

};