#include "utils.hpp"

using namespace std;


/*
给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。
----------------------------
解法：
- 动态规划 dp[i] 表示 [0,i) 问题的解 bool 型
- 递归

*/


// 思想：二分递归 + 记忆
class Solution {
    unordered_map<string, bool> mem;
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return helper(s, dict);
    }
    
    bool helper(const string& s, const unordered_set<string> & dict) {
        if (mem.count(s)) return mem[s];
        if (dict.count(s)) {
            mem[s] = true;
            return true;
        }
        // 分割成两部分考察 [0, i), [i, ~]
        for (int i=1;i<s.size();++i) {
            string left = s.substr(0, i);
            string right = s.substr(i);
            if ( helper(left, dict) && helper(right, dict) ) {
                mem[s] = true;
                return true;
            }
        }
        mem[s] = false;
        return false;
    }
};


// 动态规划，注意细节
class Solution2 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n= s.size();
        vector<int> dp(n+1, 0);  // dp[i] 表示 [0,i) 是否能被分割
        dp[0] = 1;  // base case
        for (int i=1;i<=n;++i) {
            for (int j=0;j<i;++j) {  // 当新加入一个字符，枚举分割 考察左侧是否能被分割，右侧是否在字典中  分割 [0, j) [j, ~]
                if (dp[j] && dict.count(s.substr(j, i-j)) ) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[n];
    }
};