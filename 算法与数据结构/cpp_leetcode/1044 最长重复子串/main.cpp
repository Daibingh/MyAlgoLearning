#include <bits/stdc++.h>

using namespace std;


/*
给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。
返回任何具有最长可能长度的重复子串。（如果 S 不含重复子串，那么答案为 ""。）
*/


// 最后一个示例无法通过
// 重复字符串问题求解思路：滑动窗口+字符串编码（hash）
// 此题还用到二分搜索
class Solution {
    int max_len;
    int st;
public:
    string longestDupSubstring(string S) {
        int n = S.size();
        int lo = 0, hi = n-1;
        int len;
        max_len = 0;
        st = 0;
        while (lo<=hi) {
            len = lo + (hi-lo)/2;
            if ( helper(S, len) ) {
                lo = len + 1;
            }
            else {
                hi = len - 1;
            }
        }
        return st>=0 ? S.substr(st, max_len) : "";
    }

    int helper(const string & s, int len) {
        unordered_set<unsigned int> vis;
        int l=0, r=0;
        unsigned int code = 0;
        unsigned int w = 1;
        for (;r<len;++r) {
            code = 26*code % UINT_MAX + (s[r]-'a');
            code %= UINT_MAX;
            w = w*26 % UINT_MAX;
        }
        vis.insert(code);
        for (;r<s.size();++r,++l) {
            code = 26*code % UINT_MAX - (s[l]-'a')*w % UINT_MAX + (s[r]-'a');
            if (vis.count(code)) {
                if (len > max_len) {
                    st = l+1;
                    max_len = len;
                }
                return true;
            }
            else {
                vis.insert(code);
            }
        }
        return false;
    }
};
