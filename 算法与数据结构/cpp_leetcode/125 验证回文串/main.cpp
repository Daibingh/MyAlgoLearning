#include "utils.hpp"
using namespace std;

/*
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:

输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:

输入: "race a car"
输出: false
*/


// 双指针原地比较
// 还可以清理掉额外字符，翻转判等
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.size();
        while (l<r) {
            while ( l<=r && !isalnum(s[l]) ) ++l;  // isalnum() 判断是否是 字符或数字
            while ( l<=r && !isalnum(s[r]) ) --r;
            // cout<<s[l] <<" - "<<s[r]<<endl;
            if (l>r) return true;
            if ( tolower(s[l]) != tolower(s[r]) ) return false;  // tolower() 转小写
            ++l;
            --r;  
        }
        return true;
    }
};

