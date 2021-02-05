#include <bits/stdc++.h>

using namespace std;

// 给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。

class Solution {
public:
    string addStrings(string num1, string num2) {
        string res;
        int car = 0;
        for (int i=num1.size()-1, j=num2.size()-1; i>=0 || j>=0 || car>0; --i,--j) {
            int sum = ( i>=0 ? num1[i] : '0' ) + ( j>=0 ? num2[j] : '0' ) - '0' - '0' + car;
            car = sum / 10;
            res += static_cast<char>(sum % 10 + '0');
        }
        reverse(res.begin(), res.end());
        return res;
    }
};