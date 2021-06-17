#include <bits/stdc++.h>

using namespace std;

/*
给定一个字符串 s 和一些 长度相同 的单词 words 。找出 s 中恰好可以由 words
中所有单词串联形成的子串的起始位置。 注意子串要与 words
中的单词完全匹配，中间不能有其他字符 ，但不需要考虑 words 中单词串联的顺序。
*/

class Solution {
    bool check(const string& s,
               int start,
               int len,
               int wlen,
               unordered_map<string, int> wordCnt) {
        int cnt = 0;
        for (int i = start; i <= start + len - wlen; i += wlen) {
            auto t = wordCnt.find(s.substr(i, wlen));
            if (t == wordCnt.end() || --t->second < 0)
                return false;
            ++cnt;
        }
        return cnt == len / wlen;
    }

   public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int wlen = words[0].size();
        int n = words.size();
        int len = n * wlen;
        if (len > s.size())
            return {};
        unordered_map<string, int> wordCnt;
        vector<int> res;
        for (const auto& w : words)
            ++wordCnt[w];
        for (int i = 0; i <= s.size() - len; ++i) {
            if (check(s, i, len, wlen, wordCnt))
                res.push_back(i);
        }
        return res;
    }
};