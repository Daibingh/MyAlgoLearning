#include "utils.hpp"
using namespace std;

/*
给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。

字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

说明：

字母异位词指字母相同，但排列不同的字符串。
不考虑答案输出的顺序。
*/


// 滑动窗口 使用 一个 hash 表，需要遍历 hash 表
// 时间 O(MN)
class Solution2 {
public:
        vector<int> findAnagrams(string s, string p) {
        if (s.empty() || p.empty() || p.size()>s.size()) return {};
        unordered_map<char, int> charCnt;
        for (auto & c : p) {
            ++charCnt[c];
        }
        int l = 0, r = 0;
        vector<int> res;
        for (;r<s.size();++r) {
            if (charCnt.count(s[r])) --charCnt[s[r]];
            if (r-l<p.size()-1) continue;
            if (check(charCnt)) res.push_back(l);
            if (charCnt.count(s[l])) ++charCnt[s[l]];
            ++l;
        } 
        return res;
    }

    bool check(unordered_map<char, int>& m) { 
        for (auto & t : m) {
            if (t.second) return false;
        }
        return true;
    }
};


// 滑动窗口法, 避免遍历 hash 表
// 时间 O(N) 
class Solution {
public:
        vector<int> findAnagrams(string s, string p) {
        if (s.empty() || p.empty() || p.size()>s.size()) return {};
        unordered_map<char, int> charCnt;
        for (auto & c : p) {
            ++charCnt[c];
        }
        int l = 0, r = 0;
        vector<int> res;
        int cnt = 0;
        for (;r<s.size();++r) {
            char c = s[r];
            if (charCnt.count(c)) {  // 右边界拓展
                if (--charCnt[c]==0) ++cnt;
            }
            // 左边界收缩
            while (l<=r && cnt == charCnt.size()) {
                char c = s[l];
                if (charCnt.count(c)) {
                    if (++charCnt[c]>0) --cnt;
                    if (r-l+1 == p.size()) res.push_back(l);
                }
                ++l;
            }
        } 
        return res;
    }
};
