
#include <bits/stdc++.h>

using namespace std;

/*
- https://leetcode-cn.com/problems/open-the-lock/

=================================

- 最短路径 BFS

*/

// C++ 实现
class Solution {
   public:
    int openLock(vector<string>& deadends, string target) {
        queue<string> q;
        q.push("0000");
        unordered_set<string> visted;
        for (auto s : deadends) {
            visted.insert(s);
        }
        if (visted.count("0000"))
            return -1;
        visted.insert("0000");
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string s = q.front();
                q.pop();

                if (s == target)
                    return depth;

                for (int k = 0; k < 4; ++k) {
                    char bak = s[k];
                    s[k] += 1;
                    if (s[k] > '9')
                        s[k] = '0';
                    if (!visted.count(s)) {
                        q.push(s);
                        visted.insert(s);
                    }
                    s[k] = bak - 1;
                    if (s[k] < '0')
                        s[k] = '9';
                    if (!visted.count(s)) {
                        q.push(s);
                        visted.insert(s);
                    }
                    s[k] = bak;
                }
            }
            ++depth;
        }

        return -1;
    }
};