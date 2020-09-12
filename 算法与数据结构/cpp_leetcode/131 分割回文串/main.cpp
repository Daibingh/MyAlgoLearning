#include "utils.hpp"
using namespace std;

/*
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回 s 所有可能的分割方案。
*/


class Solution {
     vector<vector<int>> mem;
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        // 动态规划做预判
        mem = vector<vector<int>>(n, vector<int>(n, 0));
        for (int i=0;i<n;++i) {
            for (int j=0;j<=i;++j) {
                mem[j][i] = (s[i]==s[j]) && ( i-j<=2 || mem[j+1][i-1]);
            }
        }
        vector<vector<string>> res;
        vector<string> path;
        // 回溯
        helper(s, res, path, 0);
        return res;
    }

    void helper(string & s, vector<vector<string>>& res, vector<string>& path, int start) {

        if (start==s.size()) {
            res.push_back(path);
            return;
        }
        
        for (int i=start;i<s.size();++i) {
            if (!mem[start][i]) continue;
            path.push_back(s.substr(start, i-start+1));
            helper(s, res, path, i+1);
            path.pop_back();
        }
    }
    
};