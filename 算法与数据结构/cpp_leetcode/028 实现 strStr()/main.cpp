#include <bits/stdc++.h>
using namespace std;

/*
实现 strStr() 函数。
给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。
如果不存在，则返回  -1。
*/

// KMP 算法
class Solution {
public:
    int strStr(string s, string p) {
        if (p.empty()) return false;
        vector<int> nxt;  // 最长公共前后缀表
        build(p, nxt);
        int i=0, j=0;
        while (i<s.size() && s.size()-i >= p.size()-j ) {
            if (j==-1 || s[i]==p[j]) {
                ++i;
                ++j;
            }
            else {
                j = nxt[j];
            }
            if (j==p.size()) return i-p.size();
        }
        return -1;
    }

    // 求最长公共前后缀的长度表，递推得到
    void build(const string& p, vector<int>& nxt) {
        nxt.resize(p.size());
        fill(nxt.begin(), nxt.end(), -1);
        int j = -1, i = 0;      // j: 前一个最长公共前后缀的长度
        while (i<p.size()-1) {
            if (j==-1 || p[i]==p[j]) {
                ++j;
                ++i;
                nxt[i] = j;
            }
            else {
                j = nxt[j];
            }
        }
    }
};

int main() {
    cout<<Solution().strStr("abdcdef", "dc")<<endl;
}