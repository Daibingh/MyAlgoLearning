#include <bits/stdc++.h>
using namespace std;


/*
给定一个正整数 n（1 ≤ n ≤ 30），输出外观数列的第 n 项。

注意：整数序列中的每一项将表示为一个字符串。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
*/


class Solution {
public:
    string countAndSay(int n) {
        string str = "1";
        for (int i=1;i<n;++i) {
            int l=0,r=0;
            string str2;
            while (l<str.size()) {
                while (r<str.size() && str[r]==str[l]) ++r;  // 双指针计数
                str2 += to_string(r-l) + str[l];
                l = r;
            }
            str = str2;
        }
        return str;
    }
};

int main() {
    
}