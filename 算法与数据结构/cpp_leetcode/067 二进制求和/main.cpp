#include "utils.hpp"
using namespace std;

/*
给你两个二进制字符串，返回它们的和（用二进制表示）。

输入为 非空 字符串且只包含数字 1 和 0。
*/

class Solution {
public:
    string addBinary(string a, string b) {
        int n = max(a.size(), b.size());
        int f = 0;
        string res;
        for (int i=0;i<n;++i) {
            int j = a.size()-i-1;
            int k = b.size()-i-1;
            f = ( j>=0 ? a[j]-'0' : 0 ) + ( k>=0 ? b[k]-'0' : 0 ) + f;
            res += (char)(f%2 + '0');
            f /= 2;
        }
        if (f) res += '1';
        reverse(res.begin(), res.end());   // std::reverse() 翻转容器
        return res;
    }
};

int main() {}