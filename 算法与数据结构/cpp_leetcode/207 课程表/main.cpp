#include "utils.hpp"

using namespace std;

/*
你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？

*/


// 利用拓扑排序判断，有向图是否有环
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> deg(numCourses,0);
        for (const auto & p : prerequisites) {
            graph[p[0]].push_back(p[1]);   // 进行拓扑排序需要两个东西：正向图，入度表； 或 反向图、出度表
            ++deg[p[1]];
        }
        queue<int> q;
        for (int i=0;i<numCourses;++i) {
            if (!deg[i]) q.push(i);
        }
        int cnt = 0;
        // 拓扑排序过程中，如果没有环 所有的节点都能变成 “零度” 的
        // 否则，最后只剩下有环的节点
        while (!q.empty()) {
            int k = q.front();
            q.pop();
            ++cnt;
            for (const auto & j : graph[k]) {
                if (--deg[j]==0) q.push(j);
            }
        }
        return cnt == numCourses;
    }
};