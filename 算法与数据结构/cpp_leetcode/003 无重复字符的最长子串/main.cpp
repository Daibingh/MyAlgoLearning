#include "utils.hpp"

using namespace std;

/**
 * 采用 hash map 数据结果，用于存储字符串对应的索引；
 * 时间复杂度 O(n), 空间复杂度 O(n)；
 * 关键在于如何更新 不重复子串的起点 start: 如果当前的字符与 [start, curr]
 * 范围内的重复，则更新 start = 重复的字符的 index + 1, 因为 visited
 * 保存了过去所有的字符，所以有可能当前字符与 [0, start)
 * 的字符重复，这种情况是不需要更新 start.
 */

class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        int start = 0;
        int res = 0;
        unordered_map<char, int> visited(s.size());
        for (auto i = 0; i < s.size(); ++i) {
            if (visited.find(s[i]) != visited.end()) {
                res = std::max(res, i - start);  // 更新长度
                start = std::max(
                    start,
                    visited[s[i]] +
                        1);  // 更新起点,
                             // 注意这里的重复有可能是与起点之前的重复，如果这样当前子串不出现重复，起点不用更新
            }
            visited[s[i]] = i;  // 更新看过的字符的索引
        }
        res = std::max(res, (int)(s.size() - start));  // 最后还要在更新一次长度
        return res;
    }
};

// 滑动窗口法 推荐
class Solution2 {
   public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        int l = 0, r = 0;
        unordered_set<char> charSet;
        for (; r < s.size(); ++r) {
            char c = s[r];
            while (l <= r &&
                   charSet.count(c)) {  // 左侧收缩的条件是，右侧字符用重复
                char d = s[l];
                charSet.erase(d);
                ++l;
            }
            charSet.insert(c);
            res = max(res, r - l + 1);
        }
        return res;
    }
};

int main() {
    string s("abba");
    auto res = Solution2().lengthOfLongestSubstring(s);
    cout << res << endl;
}