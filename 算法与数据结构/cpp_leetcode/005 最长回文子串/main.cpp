#include "../utils.hpp"

using namespace std;

/*
- 算法：DP，用一个二维 bool 数组存储 [i,j] substr 是否是 回文字符串
- 时间复杂度 O(n^2), 空间复杂度 O(n^2)
*/

class Solution {
public:

    // DP
    string longestPalindrome(string s) {
        int start = 0, end = 0;
        // deque<deque<bool>> dp(s.size(), deque<bool>(s.size(), false));  // deque 效率很低，超时！！！
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        for (auto j=0;j<s.size();++j) {
            for (auto i=0;i<j;++i) {
                if (s[i]==s[j] && (j-i<=2 || dp[i+1][j-1])) {
                    dp[i][j] = 1;
                    if (j-i>end-start) {
                        start = i;
                        end = j;
                    }
                }
            }
        }
        return s.substr(start, end-start+1);
    }

    // 中心拓展法, 在遍历的过程中，同时向两侧看
    string longestPalindrome2(string s) {
        int start = 0, end = 0;
        for (auto i=0;i<s.size();++i) {
            int len1 = expandFromMiddle(s, i, i);  // 处理 "abcba"
            int len2 = expandFromMiddle(s, i, i+1); // 处理 "abba"
            // cout<<"len1: "<<len1<<", "<<"len2: "<<len2<<endl;
            int len = std::max(len1, len2);
            if (len-1>end-start) {
                start = i - (len-1)/2;
                end = i + len/2;
            }
        }
        return s.substr(start, end-start+1);
    }

    int expandFromMiddle(const string& s, int i, int j) {
        while (i>=0 && j<s.size() && s[i]==s[j]) {
            --i;
            ++j;
        }
        return j-i-1;
    }

};

// 好写的 中心拓展法
class Solution3 {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int start=0, end=0, k1=0, k2=0;
        for (int i=0;i<n;++i) {
            tie(k1, k2) = expand(s, i, i);
            if (k2-k1 > end-start) {
                start = k1;
                end = k2;
            }
            tie(k1, k2) = expand(s, i, i+1);
            if (k2-k1 > end-start) {
                start = k1;
                end = k2;
            }
            // cout<<s.substr(start, end-start+1)<<endl;
        }
        return s.substr(start, end-start+1);
    }

    pair<int, int> expand(string & s, int i, int j) {
        while (i>=0 && j<s.size() && s[i]==s[j]) {
            --i;
            ++j;
        }

        return {i+1,j-1};
    }
};


int main() {
    auto res = Solution().longestPalindrome2("babad");
    cout<<res<<endl;
}