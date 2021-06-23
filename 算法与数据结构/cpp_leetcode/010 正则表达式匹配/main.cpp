#include "../utils.hpp"

using namespace std;

/*
- 用递归解法简单，动态规划较为繁琐
- C++ substr(pos, n) 字符串截取
*/

class Solution {
   public:
    // 解法 1：递归
    bool isMatch(string s, string p) {
        if (p.empty())
            return s.empty();  // p 要是空，则 s 一定是空才能匹配

        bool firstMatch =!s.empty() && (p[0] == s[0] || p[0] == '.');  // 走一步(先看看第一个字符是否匹配)
        if (p.size() >= 2 && p[1] == '*') {  // 如果第二个字符是 '*', 分两种情况：1) x* 匹配0个字符;
                                            // 2) x* 匹配1个以上字符
            return isMatch(s, p.substr(2)) || firstMatch && isMatch(s.substr(1), p);
        } else {  // 不是 '*' 好说，直接从第二个字符开始看
            return firstMatch && isMatch(s.substr(1), p.substr(1));
        }
    }
};

// 另一种写法
class Solution2 {
   public:
    bool isMatch(string s, string p) { return helper(s, p, 0, 0); }

    bool helper(const string& s, const string& p, int i, int j) {
        if (j >= p.size())
            return i >= s.size();  // 终止条件 p 为空
        bool f = i < s.size() && (p[j] == '.' || s[i] == p[j]);  // 先判断首字符是否匹配
        if (j < p.size() - 1 && p[j + 1] == '*')
            return helper(s, p, i, j + 2) || f && helper(s, p, i + 1, j);  // 或的前后顺序有影响！
        else
            return f && helper(s, p, i + 1, j + 1);
    }
};

int main() {
    cout << Solution().isMatch("bc", "a*bc") << endl;
}