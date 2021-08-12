/*
https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
---

*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l = 0, r = 0;
        unordered_set<char> charset;
        int res = 0;
        while (r<s.size()) {
            while (l<r && charset.count(s[r])) {  // 左指针移动条件
                charset.erase(s[l]);
                ++l;
            }
            charset.insert(s[r]);  // 右指针移动
            ++r;
            res = max(r-l, res);
        }
        return res;
    }
};