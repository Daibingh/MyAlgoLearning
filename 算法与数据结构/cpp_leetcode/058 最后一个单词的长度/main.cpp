#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

class Solution {
   public:
    int lengthOfLastWord(string s) {
        auto it = s.rbegin();
        for (; it != s.rend() && *it == ' '; ++it)
            ;  // 跳过末尾空白
        int cnt = 0;
        for (; it != s.rend() && *it != ' '; ++it, ++cnt)
            ;  // 计数最后单词数目
        return cnt;
    }
};

int main() {}