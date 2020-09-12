#include "utils.hpp"
using namespace std;

/*
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

示例 1:

输入: s = "anagram", t = "nagaram"
输出: true
*/

// 排序比较
class Solution2 {
public:
    bool isAnagram(string s, string t) {
        if (s.size()!=t.size()) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s==t;
    }
};

// 分桶计数
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size()!=t.size()) return false;
        vector<int> cnt(26,0);
        for (auto & c : s) {
            ++cnt[c-'a'];
        }
        for (auto & c : t) {
            --cnt[c-'a'];
        }
        for (int i=0;i<26;++i) {
            if (cnt[i]) return false;
        }
        return true;
    }
};
