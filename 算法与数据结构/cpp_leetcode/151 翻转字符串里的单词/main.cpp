#include "utils.hpp"

using namespace std;

class Solution {
public:

    // 解法 1：扫描提取 word, prepend 字符串, out-place 操作
    string reverseWords2(string s) {
        if (s.empty()) return "";
        int p1=0, p2=0;
        string res;
        while (p1<s.size()) {
            while (p1<s.size() && s[p1]==' ') ++p1;
            p2 = p1;
            while (p2<s.size() && s[p2]!=' ') ++p2;
            if (p2>p1) res = s.substr(p1, p2-p1) + " " + res;
            p1 = p2;
        }
        if (!res.empty()) res.pop_back();
        return res;
    }
    
    // 解法 2：inplace 操作，先整体翻转，然后 word 翻转
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int l=0, r=0;
        while (l<s.size()) {
            int cnt = 0;
            while (l<s.size() && s[l]==' ') {
                ++cnt;
                if (cnt>1) {  // 出现连续两个空格，就删除
                    s.erase(s.begin()+l); // 从前到后，遍历删除 it 位置，不同更新 it
                }
                else ++l;
            }
            r = l;
            while (r<s.size() && s[r]!=' ') ++r;
            reverse(s.begin()+l, s.begin()+r);
            l = r;
        }
        // 去除头部空白
        for (auto it=s.begin();it!=s.end();) {
            if (*it==' ') it = s.erase (it);
            else break;
        }
        // 去除尾部空白
        for (auto it=s.rbegin();it!=s.rend();++it) {
             if (*it==' ') s.pop_back();
            else break;
        }
        return s;
    }

    // 解法 3：使用 stringstream 过滤空白
};