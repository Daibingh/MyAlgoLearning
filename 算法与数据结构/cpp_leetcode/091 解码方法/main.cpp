#include "utils.hpp"
using namespace std;

/*
一条包含字母 A-Z 的消息通过以下方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。

示例 1:

输入: "12"
输出: 2
解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。
示例 2:

输入: "226"
输出: 3
解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
*/

// 记忆搜索 递归
class Solution {
    unordered_map<int, int> mem;
public:
    int numDecodings(string s) {
        return helper(s, 0);
    }

    int helper(string & s, int i) {
        if (mem.count(i)) return mem[i];
        if (i==s.size()) return 1;
        if (i>s.size()) return 0;

        int ret1 = s[i]>'0' ? helper(s, i+1) : 0;
        int ret2 = s[i]=='1' || ( s[i]=='2' && s[i+1]<'7' ) ?  helper(s, i+2) : 0;
        int ret =  ret1 + ret2;
        return mem[i] = ret;
    }
};


// 动态规划
class Solution2 {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0]=='0') return 0;
        if (s.size()==1) return 1;
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for (int i=1;i<=n;++i) {
            int part1 = s[i-1]!='0' ? dp[i-1] : 0 ;
            int part2 = i>=2 && ( s[i-2]=='1' || ( s[i-2]=='2' && s[i-1]<'7' ) ) ? dp[i-2] : 0;
            dp[i] = part1 + part2; 
        }
        return dp.back();
    }

};
