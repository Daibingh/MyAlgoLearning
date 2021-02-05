#include <bits/stdc++.h>
using namespace std;

/*
给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

有效的 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是 有效的 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效的 IP 地址。

*/

// 回溯，类似于爬楼梯，字符串解码
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        string str;
        helper(res, str, s, 0, 0);
        return res;
    }

    void helper(vector<string>& res, string str, string& s, int i, int k) {
        if ( ( s.size()-i ) / (4.-k) > 3 ) return ; 
        if (i>=s.size()) {
            if (k==4) {
                str.pop_back();
                res.push_back(str);
            }
            return;
        }

        if (s[i]=='0') {
            helper(res, str+"0.", s, i+1, k+1);
        }
        else 
            for (int j=i;j<s.size() && j<i+3;++j) {
                if (stoi(s.substr(i, j-i+1))<=255) {
                    helper(res, str+s.substr(i, j-i+1)+".", s, j+1, k+1);
                }
            }
    }
};