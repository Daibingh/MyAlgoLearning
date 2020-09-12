#include "utils.hpp"

using namespace std;

/*
给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。

示例：

输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"
-----------------------------------
分析：
- 滑动窗口思想: 右指针探索满足条件的区间，左指针缩减区间寻找最优, 窗口大小先增后减，反复进行
- 相似题目：567. 字符串的排列，3. 无重复字符的最长子串

*/

// 滑动窗口法，遍历hash判断是否匹配
// 时间复杂度 O(n*c)
// 用到两个 hash 表，也可以只用一个，存差值
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> ch_cnt, ch_cnt2;
        for (const auto & c : t) ++ch_cnt[c];

        // print_dict(ch_cnt);
        
        string res;
        int min_len = INT_MAX;
        
        int l=0, r=0;
        
        while (r<s.size()) {
            char c = s[r];
            if (ch_cnt.find(c)!=ch_cnt.end()) {
                ++ch_cnt2[c];
            }             
            ++r;  // 注意：右指针先用后加，所以窗口区间为 [l, r)
            
            // print_dict(ch_cnt2);

            while (check(ch_cnt, ch_cnt2) && l < r ) {
                if (r-l < min_len) {
                    min_len = r-l;
                    res = s.substr(l, min_len);
                }
                 char c = s[l];
                 if (ch_cnt.find(c)!=ch_cnt.end()) {
                    --ch_cnt2[c];
                }      
                ++l;
            }
        }
        return res;
        
    }
    
    bool check(unordered_map<char, int>& ch_cnt, unordered_map<char, int>&  ch_cnt2) {
        for (const auto & m : ch_cnt) {
            if (ch_cnt2.find(m.first)==ch_cnt2.end() || m.second > ch_cnt2[m.first]) return false;  // 注意：这里不同严格判断 != , 因为某个字符 >= t 中的字符，仍满足要求 
        }
        return true;
    }
};


// 滑动窗口法，避免遍历hash表
// 时间复杂度 O(N) 用一个变量记录当前窗口与 t 字符匹配的个数
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> charCnt;
        for (auto & c : t) {
            ++charCnt[c];
        }
        int cnt = 0;  // 字符匹配的个数
        int l = 0, r = 0;
        string res;
        int len = INT_MAX;
        int m = charCnt.size();
        for (;r<s.size();++r) {
            char c = s[r];
            if (--charCnt[c]==0) 
                ++cnt;
            while (l<=r && cnt==m) {
                if (r-l+1 < len) {
                    len = r-l+1;
                    res = s.substr(l, len);
                }
                char c = s[l];
                if (++charCnt[c] > 0) --cnt;
                ++l;  // ++l 在更新答案之后！
            }
        }
        return res;
    }
};

int main() {
    
    string s, t;
    s = "ADOBECODEBANC";
    t = "ABC";
    auto res = Solution().minWindow(s,t);
    cout<<res<<endl;
    return 0;
}