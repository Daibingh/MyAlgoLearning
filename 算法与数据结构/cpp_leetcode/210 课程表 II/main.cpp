#include "utils.hpp"
using namespace std;

/*
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。

示例 1:

输入: 2, [[1,0]] 
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1]
*/


// 拓扑排序
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> deg(numCourses);
        for (auto & p : prerequisites) {
            graph[ p[1] ].push_back( p[0] );
            ++deg[ p[0] ];
        }
        queue<int> q;
        for (int i=0;i<numCourses;++i) {
            if (!deg[i]) q.push(i);
        }
        vector<int> res;
        while (!q.empty()) {
            int n = q.front();
            res.push_back(n);
            q.pop();
            for (auto & t : graph[n]) {
                if (--deg[t]==0) q.push(t);
            }
        }
        return res.size() == numCourses ? res : vector<int>();
    }
};
