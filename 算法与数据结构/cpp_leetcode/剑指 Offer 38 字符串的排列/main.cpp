#include <bits/stdc++.h>
using namespace std;


/*
输入一个字符串，打印出该字符串中字符的所有排列。

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

示例:

输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]

*/

// dfs 要注意去重，”aab“
class Solution {
public:
    vector<string> permutation(string s) {
        vector<string> res;
        string path;
        sort(s.begin(), s.end());   // 先排序，便于后面去重
        helper(res, path, s);
        return res;
    }

    void helper(vector<string>& res, string& path, string& s) {

        if (path.size()==s.size()) {
            res.push_back(path);
            return;
        }
        
        for (int i=0;i<s.size();++i) {
            if (s[i]==' ' ||  (i>0 && s[i]==s[i-1] ) ) continue;   // 去重 相邻的重复数字就不要往下搜索了
            char ch = s[i];
            s[i] = ' ';
            path += ch;
            helper(res, path, s);
            s[i] = ch;
            path.pop_back();
        }
    }
};
