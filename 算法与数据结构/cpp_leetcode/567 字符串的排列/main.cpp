#include "utils.hpp"
using namespace std;


/*
给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。

换句话说，第一个字符串的排列之一是第二个字符串的子串。
------------------------------------------------
分析：
- **滑动窗口**思想，用大小恒定的窗口扫描，统计字符个数差值
- 相似题目：76. 最小覆盖子串，3. 无重复字符的最长子串
*/


class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        
        if (s1.size()>s2.size()) return false;
        
        unordered_map<char, int> ch_cnt;
        for (const auto & c: s1) ++ch_cnt[c];
        int l=0, r=0;
        while (r<s1.size()) {
            char c = s2[r];
            if (ch_cnt.find(c)!=ch_cnt.end()) {
                --ch_cnt[c];
            }
            ++r;
        }
        if (check(ch_cnt)) return true;

        while (r<s2.size()) {
            
            char c = s2[r];
            if (ch_cnt.find(c)!=ch_cnt.end()) {
                --ch_cnt[c];
            }
            ++r;
            
            c = s2[l];
             if (ch_cnt.find(c)!=ch_cnt.end()) {
                ++ch_cnt[c];
            }
            ++l;

            if (check(ch_cnt)) return true;
        }
        
        return false;
    }
    
    bool check(unordered_map<char, int>& ch_cnt) {
        for (auto & m : ch_cnt) {
            if (m.second) return false;
        }
        return true;
    }
};

// 滑动窗口法 推荐
class Solution2 {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.empty()) return !s2.empty();
        int l = 0, r = 0;
        unordered_map<char, int> charCnt;
        for (auto & c : s1) {
            ++charCnt[c];
        }
        for (;r<s2.size();++r) {
            char c = s2[r];
            --charCnt[c];  // 右侧先收录一个字符
            while (l<=r && charCnt[c]<0) {  // 左边界收缩的条件是 右边界字符 有冗余
                char d = s2[l]; 
                ++charCnt[d];
                ++l;
            }
            if (r-l+1==s1.size()) return true;

        }
        return false;
    }
};

// 滑动窗口，左边界收缩的条件不一致
class Solution3 {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.empty()) return !s2.empty();
        int l = 0, r = 0;
        unordered_map<char, int> charCnt;
        for (auto & c : s1) {
            ++charCnt[c];
        }
        int cnt = 0;
        for (;r<s2.size();++r) {
            char c = s2[r];
            if (charCnt.count(c) && --charCnt[c]==0) ++cnt;
            while (l<=r && cnt==charCnt.size()) {
                if (r-l+1==s1.size()) return true;
                char d = s2[l];
                if (charCnt.count(d) && ++charCnt[d]>0) --cnt;
                ++l;
            }
        }
        return false;
    }
};

int main() {
    
}
