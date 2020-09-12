#include "utils.hpp"
using namespace std;

/*
给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。

示例 1:

输入: [10,2]
输出: 210
示例 2:

输入: [3,30,34,5,9]
输出: 9534330
说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。

*/


// 这种方法有点麻烦，但是好像更快点
class Solution {
    static bool comp(const string& s1, const string & s2) {
        return stol(s1+s2) < stol(s2+s1);
        
    }
public:
    string largestNumber(vector<int>& nums) {
        vector<string> tmp;
        for (auto & t : nums) {
            tmp.push_back(to_string(t));
        }
        sort(tmp.rbegin(), tmp.rend(), comp);
        if (tmp[0]=="0") return "0";
        string res;
        for (auto & t : tmp) {
            res += t;
        }
        return res;
    }
};


class Solution2 {
public:
    string largestNumber(vector<int>& nums) {
        // 直接对字符串 自定义排序
        sort( nums.begin(), nums.end(), [](int a, int b){
            return to_string(a)+to_string(b)>to_string(b)+to_string(a);
            } );
        if (nums[0]==0) return "0";  // 特判
        string res;
        for (auto & t : nums) {
            res += to_string(t);
        }
        return res;
    }
};